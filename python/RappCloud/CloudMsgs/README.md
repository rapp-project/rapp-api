- [Cloud Messages - General description](https://github.com/rapp-project/rapp-api/blob/python/python/RappCloud/CloudMsgs/README.md#cloud-messages)
- RAPP Platform API Python calls
  - [Cognitive Exercises - Test Selector](#cognitive-exercises---test-selector)
  - [Cognitive Exercises - Get History Records](#cognitive-exercises---get-history-records)
  - [Cognitive Exercises - Get Scores](#cognitive-exercises---get-scores)
  - [Cognitive Exercises - Record Performance](#cognitive-exercises---record-performance)
  - [Email - Fetch Received Emails](#email---fetch-received-emails)
  - [Email - Send](#email---send)
  - [Face detection](#face-detection)
  - [Geolocation](#geolocation)
  - [Human detection](#human-detection)
  - [Hazard detection - Door](#hazard-detection---door)
  - [Hazard detection - Lights](#hazard-detection---lights)
  - [News Explorer](#news-explorer)
  - [Object recognition Caffe](#object-recognition-caffe)
  - [Ontology Query - Subclasses of](#ontology-query---subclasses-of)
  - [Ontology Query - Superclasses of](#ontology-query---superclasses-of)
  - [Ontology Query - Is Subsuperclass of](#ontology-query---is-subsuperclass-of)
  - [Path Planning - Plan Path 2D](#path-planning---plan-path-2d)
  - [Path Planning - Upload Map](#path-planning---upload-map)
  - [Qr detection](#qr-detection)
  - [Set Noise Profile](#set-noise-profile)
  - [Speech Recognition Sphinx](#speech-recognition-sphinx)
  - [Speech Recognition Google](#speech-recognition-google)
  - [Text To Speech](#text-to-speech)
  - [Weather Reporter - Current Weather](#weather-reporter---current-weather)
  - [Weather Reporter - Forecast](#weather-reporter---forecast)
  - [User Personal Info](#user-personal-info)

# Cloud Messages - General description

A complete list and description of the `CloudMsg` classes.

`CloudMsg` classes include:
- Request object.
- Response object.

All CloudMsg classes inherit from the `CloudMsg` class:

```py
from Cloud import CloudMsg

class MockMsg(CloudMsg):
    def __init__(self, **kwargs):
        pass
```

Each `CloudMsg` inherited class has a `Request` and `Response` class. `Request` classes
inherit from `CloudRequest` class and `Response` inherits from `CloudResponse`:

```py
from Cloud import (
  CloudMsg,
  CloudRequest,
  CloudResponse)

class MockMsg(CloudMsg):
    class Request(CloudRequest):
        def __init__(self, **kwargs):
            pass

    class Response(CloudResponse):
        def __init__(self, **kwargs):
            pass

    def __init__(self, **kwargs):
        pass
```

Each `Request` class of a `CloudMsg` must implement the following methods:

- `make_payload()`: Create and return a `Payload` object. This is the data payload to send to the RAPP Platform Service, except files. The `File` object is used as a container of sending files to the RAPP Platform Services.
- `make_files()` Create and return Array of `File` objects

```py
from RappCloud.Objects import (
    Payload,
    File)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)

class MockMsg(CloudMsg):
    class Request(CloudRequest):
        def __init__(self, **kwargs):
            pass
            
        def make_payload(self):
            # Empty Payload. No data will be send
            return Payload()
            
        def make_files(self):
            # Return an empty array. In case of sending files this method should return an array of `File` objects.
            return []

    class Response(CloudResponse):
        def __init__(self, **kwargs):
            pass

    def __init__(self, **kwargs):
        pass
```


**Creating `Payload` objects**

Simply pass the key-value pairs to the `Payload` constructor

```py
from RappCloud.Objects import Payload

payload = Payload(prop_1: "test", prop_2: 10)
print payload.prop_1
>> "test"
print payload.prop_2
>> 10
```

**Creating `File` objects**

A `File` is described by a `filepath` and a `postfield`.

The `postfield` is the field name, of the http form, to append the file (multipart/form-data). This is the field name that the RAPP Platform Web Service parse for received files.

You can set those values by passing to the `File` constructor, or using the **dot notation**.

```python
from RappCloud.Objects import File

f1 = File(filepath="PATH", postfield="POST_FIELD_NAME")

f2 = File()
f2.path = "PATH"
f2.postfield = "POST_FIELD_NAME"
```


***

## Face detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Face-Detection)

**Request object: FaceDetection.Request**
```python
# System path to the image file
String imageFilepath

# If true, detection will take less time but it will be less accurate
Bool fast
```

**Response object: FaceDetection.Response**
```python
# Found faces 2D points. A face is described by an up_left_point and a down_right_point in cartesian coordinates:
# face: { up_left_point: {<point2D>}, down_right_point: {<point2D>} } where point2D is an object of structure:
# point2D: { x: <value_int>, y: <value_int> }
Array faces

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import FaceDetection
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = FaceDetection()

# System path to the image file
msg.req.imageFilepath = "PATH"
# If true, detection will take less time but it will be less accurate
msg.req.fast = True

response = svc.call(msg)
```

**Example output**:
```python
print response.faces
>> [ { up_left_point: {x: 0, y: 0}, down_right_point: {x: 100, y: 100} } ]
print response.error
>> ""
```

***

## Qr detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-QR-Detection)

**Request object: QrDetection.Request**
```python
# System path to the image file
String imageFilepath
```

**Response object: QrDetection.Response**
```python
# Center points (point2D) of found QR codes
# qr_centers: [{<point2D_1>}, ..., {<point2D_n>}] where point2D is an object of structure:
# point2D: { x: <value_int>, y: <value_int> }
Array qr_centers

# Qr description messages of found QR codes (point2D)
# qr_messages: ['rapp project qr sample']
Array qr_messages

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import QrDetection
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = QrDetection()

# System path to the image file
msg.req.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.qr_centers
>> [ {x: 0, y: 0}, {x: 100, y: 100} ]
print response.qr_messages
>> [ 'test 1', 'test 2' ]
print response.error
>> ""
```

***

## Human detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Human-Detection)

**Request object: HumanDetection.Request**
```python
# System path to the image file
String imageFilepath
```

**Response object: HumanDetection.Response**
```python
# Array of detected humans
# humans: [ {<human_1>}, ..., {<human_n>} ] where human_x is an object of structure:
# human: { up_left_point: {x: 0, y: 0}, down_right_point: {x: 0, y: 0} }
Array humans

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import HumanDetection
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = HumanDetection()

# System path to the image file
msg.req.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.humans
>> [ {up_left_point: {x: 0, y: 0}, down_right_point: {x: 100, y: 100} } ]
print response.error
>> ""
```

***

## Hazard detection - Door

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Hazard-Detection)

**Request object: HazardDetectionDoor.Request**
```python
# System path to the image file
String imageFilepath
```

**Response object: HazardDetectionDoor.Response**
```python
# The angle of the detected open door
Float door_angle

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import HazardDetectionDoor
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = HazardDetectionDoor()

# System path to the image file
msg.req.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.door_angle
>> 0.83
print response.error
>> ""
```

***

## Hazard detection - Lights

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Hazard-Detection)

**Request object: HazardDetectionLight.Request**
```python
# System path to the image file
String imageFilepath
```

**Response object: HazardDetectionLight.Response**
```python
# The, detected on the image frame, light level.
Float light_level

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import HazardDetectionLight
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = HazardDetectionLight()

# System path to the image file
msg.req.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.light_level
>> 100
print response.error
>> ""
```

***

## Object recognition Caffe

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Caffe-Wrapper)

**Request object: ObjectRecognitionCaffe.Request**
```python
# System path to the image file
String imageFilepath
```

**Response object: ObjectRecognitionCaffe.Response**
```python
# Recognized object class
String object_class

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import ObjectRecognitionCaffe
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = ObjectRecognitionCaffe()

# System path to the image file
msg.req.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.object_class
>> "television"
print response.error
>> ""
```

***

## Set Noise Profile

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Audio-Processing)

**Request object: SetNoiseProfile.Request**
```python
# System path to the audio file
String audiofile

# Audio source type/format. e.g. "nao_wav_1_ch"
String audio_source
```

**Response object: SetNoiseProfile.Response**
```python
# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import SetNoiseProfile
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = SetNoiseProfile()

# System path to the image file
msg.req.audiofile = "PATH"
# Audio source type/format. e.g. "nao_wav_1_ch"
msg.req.audio_source = "nao_wav_1_ch"

response = svc.call(msg)
```

**Example output**:
```python
print response.error
>> ""
```

***

## Speech Recognition Sphinx

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Speech-Detection-using-Sphinx4)

**Request object: SpeechRecognitionSphinx.Request**

```python
# System path to the audio file
String audiofile

# Audio source type/format. e.g. "nao_wav_1_ch"
String audio_source

# Language to use for speech recognition
String language

# Array of words to recognize
Array words

# Under consideration sentences
Array sentences

# Grammar to use
Array grammar
```

**Response object: SpeechRecognitionSphinx.Response**
```python
# Recognized words
Array words

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import SpeechRecognitionSphinx
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = SpeechRecognitionSphinx()

# System path to the image file
msg.req.audiofile = "PATH"
# Audio source type/format. e.g. "nao_wav_1_ch"
msg.req.audio_source = "nao_wav_1_ch"
# Language to use for speech recognition
msg.req.language = 'en'
# Array of words to recognize
msg.req.words = ['yes', 'no']
# Under consideration sentences
msg.req.sentences = msg.req.words
# Grammar to use
msg.req.grammar = []

response = svc.call(msg)
```

**Example output**:
```python
print response.words
>> ['yes']
print response.error
>> ""
```

***

## Speech Recognition Google 

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Speech-Detection-using-Google-API)

**Request object: SpeechRecognitionGoogle.Request**


```py
# System path to the audio file
String audiofile

# Audio source type/format. e.g. "nao_wav_1_ch"
String audio_source

# Language to use for speech recognition
String language
```

**Response object: SpeechRecognitionGoogle.Response**

```py
# Recognized words with highest confidence
Array words

# Alternative sentences
Array alternatives

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import SpeechRecognitionGoogle
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = SpeechRecognitionGoogle()

# System path to the image file
msg.req.audiofile = "PATH"
# Audio source type/format. e.g. "nao_wav_1_ch"
msg.req.audio_source = "nao_wav_1_ch"
# Language to use for speech recognition
msg.req.language = 'en'

response = svc.call(msg)
```

**Example output**:
```python
print response.words
>> ['I', 'want', 'to', 'go', 'out']
print response.alternatives
>> [['I', 'want', 'to', 'go', 'up'], ['I', 'want', 'to', 'grow', 'up']]
print response.error
>> ""
```

***

## Ontology Query - Subclasses of

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Knowrob-wrapper)

**Request object: OntologySubclasses.Request**

```py
# The query to the ontology database
String ontology_class
# Recursive search
Bool recursive
```

**Response object: OntologySubclasses.Response**

```py
# Ontology query results.
Array results

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import OntologySubclasses
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = OntologySubclasses()
# Ontology subclasses of Oven query
msg.req.ontology_class = 'Oven'
msg.req.recursive = False

response = svc.call(msg)
```


**Example output**:
```python
print response.results
>> [u'http://knowrob.org/kb/knowrob.owl#MicrowaveOven', u'http://knowrob.org/kb/knowrob.owl#RegularOven', u'http://knowrob.org/kb/knowrob.owl#ToasterOven']
print response.error
>> ""
```

***

## Ontology Query - Superclasses of

**Description [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Knowrob-wrapper)**

**Request object: OntologySuperclasses.Request**

```python
# The query to the ontology database
String ontology_class
# Recursive search
Bool recursive
```

**Response object: OntologySuperclasses.Response**

```python
# Ontology query results.
Array results

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import OntologySuperclasses
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = OntologySuperclasses()
# Ontology superclasses of Oven query
msg.req.ontology_class = 'Oven'
msg.req.recursive = False

response = svc.call(msg)
```


**Example output**:
```python
print response.results
>> [u'http://knowrob.org/kb/knowrob.owl#Box-Container', u'http://knowrob.org/kb/knowrob.owl#FurniturePiece', u'http://knowrob.org/kb/knowrob.owl#HeatingDevice', u'http://knowrob.org/kb/knowrob.owl#HouseholdAppliance']
print response.error
>> ""
```

***

## Ontology Query - Is Subsuperclass of

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Knowrob-wrapper)

**Request object: OntologyIsSubsuperclass.Request**

```python
# The parent class
String parent_class

# The child class
String child_class

# Recursive search
Bool recursive
```

**Response object: OntologyIsSubsuperclass.Response**

```python
# Ontology query result.
Bool result

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import OntologyIsSubsuperclass
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = OntologyIsSubsuperclass()
# Parent class
msg.req.parent_class = 'Oven'
# Child class
msg.req.child_class = 'Microwave'

response = svc.call(msg)
```


**Example output**:
```python
print response.result
>> True
print response.error
>> ""
```


***


## Cognitive Exercises - Test Selector

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Request object: CognitiveExerciseSelect.Request**
```python
# Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
# https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise
String test_type

# Force select exercise from this subtype. Depends on test_type value
String test_subtype

# Force select exercise from this difficulty. Depends on test_type and test_subtype values
String test_diff

# Force select exercise index. Depends on test_type, test_subtype and test_diff values
String test_index
```

**Response object: CognitiveExerciseSelect.Response**
```python
# Set of questions for the exercise
Array questions

# Set of possible answers for each question
Array possib_ans

# Set of correct answers for each question
Array correct_ans

# Test instance name
String test_instance

# The selected exercise type
String test_type

# The selected exercise sub_type
String test_subtype

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import CognitiveExerciseSelect
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = CognitiveExerciseSelect()

# Test type
msg.req.test_type = 'ArithmeticCts'
# Test subtype
msg.req.test_subtype = 'TransactionChangeCts'
# Test difficulty
msg.req.test_diff = '1'
# Test index
msg.req.test_index = '1'

response = svc.call(msg)
```


**Example output**:
```python
print response.test_type
>> "ArithmeticCts"
print response.test_subtype
>> "TransactionChangeCts"
print response.test_instance
>> ArithmeticCts_stXqnGrc
print response.questions
>> [ "Q1", "Q2", ... ]
print response.possib_ans
>> [ ["Q1_PA1", "Q1_PA2", ...], ["Q2_PA1", "Q2_PA2", ...], ... ]
print response.correct_ans
>> [ "Q1_CA", "Q2_CA", ... ]
print response.error
>> ""
```


***


## Cognitive Exercises - Get History Records

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)


**Request object: CognitiveGetHistory.Request**
```python
# Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
# https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise
String test_type

# Unix timestamp
Int time_from

# Unix timestamp
Int time_to
```


**Response object: CognitiveGetHistory.Response**
```python
# History records
Dict records

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import CognitiveGetHistory
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = CognitiveGetHistory()

# Test type ('' == ALL)
msg.req.test_type = ''
# Time from value
msg.req.time_from = 0
# Time to value
msg.req.time_to = 100000000

response = svc.call(msg)
```


**Example output**:
```python
print response.records
>> {u'reasoningcts': [], u'arithmeticcts': [], u'awarenesscts': []}
print response.error
>> ""
```


***


## Cognitive Exercises - Get Scores

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Request object: CognitiveGetScores.Request**
```python
# Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
# https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise
String test_type

# Unix timestamp
Int time_to
```


**Response object: CognitiveGetScores.Response**
```python
# Test classes indexes
Array test_classes

# Scores. Each array index corresponds to the test class in test_classes
Array scores

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import CognitiveGetScores
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = CognitiveGetScores()

# Test type ('' == ALL)
msg.req.test_type = ''
# Time to value
msg.req.time_to = 100000000

response = svc.call(msg)
```


**Example output**:
```python
print response.test_classes
>> [u'ArithmeticCts', u'ReasoningCts', u'AwarenessCts']
print response.scores
>> [0.0, 0.0, 0.0]
print response.error
>> ""
```


***


## Cognitive Exercises - Record Performance

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)


**Request object: CognitiveRecordPerformance.Request**
```python
# The exercise test instance name (Returned by CognitiveExerciseSelect)
String test_instance

# Performance score to record
Int score
```

**Response object: CognitiveRecordPerformance.Response**

```
# Cognitive exercise performance entry in ontology.
String performance_entry

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import CognitiveRecordPerformance
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = CognitiveRecordPerformance()

# Test instance (Returned by calling CognitiveExerciseSelect)
msg.req.test_instance = 'ArithmeticCts_stXqnGrc'
# Performance score to record
msg.req.score = 40

response = svc.call(msg)
```


**Example output**:
```python
print response.performance_entry
>> "http://knowrob.org/kb/knowrob.owl#CognitiveTestPerformed_gaOpMBqF"
print response.error
>> ""
```


***


## Email - Fetch Received Emails

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Email)


**Request object: EmailFetch.Request**
```python
# Email account username
String email

# Email account password
String password

# The email server imap address, i.e. 'imap.gmail.com'.
String server

# The email server imap port. Leave empty to use default value.
String port

# Emails since date. Unix timestamp.
Int date_from

# Emails until date. Unix timestamp.
Int date_to

# Define which mails the users requests. Values: ALL, UNSEEN(DEFAULT)
String email_status

# Number of emails to fetch.
Int num_emails
```


**Response object: EmailFetch.Response**
```python
# Array of emailEntry objects, where emailEntry is of structure:
# { sender: '', receivers: [], date: '', body: '', attachments: [] }
Array emails

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import EmailFetch 
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = EmailFetch()

# Email account name
msg.req.email = "EMAIL_ACCOUNT_NAME"
# Email account password
msg.req.password = "EMAIL_PASSWORD"
# The imap address of the email server/provider
msg.req.server = "imap.gmail.com"
# The listening port number of the imap server/providrer
msg.req.port = ""
# Fetch received emails from this date value.
msg.req.date_from = "0"
# Fetch emails up to this date value.
# Max number of emails to fetch
msg.req.num_emails = 5

response = svc.call(msg)
```


**Example output**:
```python
print response.emails
>> { sender: 'SENDER_EMAIL', receivers: ["R1", "R2"], body: 'Body of the email', date: '', attachments: [] }
print response.error
>> ""
```



***


## Email - Send

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Email)


**Request object: EmailSend.Request**
```python
# Email account username
String email

# Email account password
String password

# The email server imap address, i.e. 'imap.gmail.com'.
String server

# The email server imap port. Leave empty to use default value.
String port

# Email addresses of the recipients
Array recipients

# Email body content
String body

# Email subject
String subject

# Attachment file path. Can be a .zip file that will be decompressed on the server.
String attach_file
```

**Response object: EmailSend.Response**

```python
# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import EmailSend
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = EmailSend()

# Email account name
msg.req.email = "EMAIL_ACCOUNT_NAME"
# Email account password
msg.req.password = "EMAIL_PASSWORD"
# The imap address of the email server/provider
msg.req.server = "imap.gmail.com"
# The listening port number of the imap server/providrer
msg.req.port = ""
msg.req.body = "Test sending email"
msg.req.subject = "Test sending email"
msg.req.recipients = ["RECIPIENT_1", "RECIPIENT_2"]

response = svc.call(msg)
```


**Example output**:
```python
print response.error
>> ""
```


***


## Weather Reporter - Current Weather

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Weather-Reporter)


**Request object: WeatherReportCurrent.Request**
```python
# The desired city
String city

# The weather API to use. Defaults to "yweather" .
String weather_reporter

# The return value units.
Int metric
```


**Response object: WeatherReportCurrent.Response**
```python
# Current date
String date

# Current temperature
String temperature

# A brief description of the current weather
String weather_description

# Current humidity
String humidity

# Current visibility
String visibility

# Current pressure
String pressure

# Current speed of the wind
String wind_speed

# Current temperature of the wind
String wind_temperature

# Current wind direction
String wind_direction

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import WeatherReportCurrent
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = WeatherReportCurrent()

msg.req.city = "Athens"

response = svc.call(msg)
```


**Example output**:
```python
print response.temperature
>> 21
print response.error
>> ""
```



## Weather Reporter - Forecast

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Weather-Reporter)


**Request object: WeatherReportForecast.Request**
```python
# The desired city
String city

# The weather API to use. Defaults to "yweather" .
String weather_reporter

# The return value units.
Int metric
```

**Response object: WeatherReportForecast.Response**

```
# Array of forecastEntry objects, where forecastEntry is of structure:
# { high_temp: '', low_temp: '', description: '', date: '' }
Array forecast

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import WeatherReportForecast
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = WeatherReportForecast()

msg.req.city = "Athens"

response = svc.call(msg)
```


**Example output**:
```python
print response.forecast
>> [ {FORECAST_ENTRY_1}, {FORECAST_ENTRY_2} ]
print response.error
>> ""
```


***


## Path Planning - Plan Path 2D

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Path-planner)


**Request object: PathPlanningPlan2D.Request**
```python
# The name of the, stored to the Platform, map
String map_name

# The robot type. It is required to determine it's parameters (footprint etc.)
String robot_type

# The path planning algorithm to apply.
String algorithm

# Start pose of the robot. Same structure to ROS-GeometryMsgs/PoseStamped
Dict pose_start

# Goal pose of the robot. Same structure to ROS-GeometryMsgs/PoseStamped
Dict pose_goal
```

**Response object: PathPlanningPlan2D.Response**
```python
# Plan status: https://github.com/rapp-project/rapp-platform/wiki/RAPP-Path-planner
Int plan_found

# If plan_found is equal to 0 (path found), this is an array of waypoints from start to goal.
Array path

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import PathPlanningPlan2D 
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = PathPlanningPlan2D()

# The map name as previously upload to the Platform (look at [PathPlanningUploadMap](#path-planning-upload-map))
msg.req.map_name = "MAP_NAME"
# The type of robot executing path planning. In this case NAO robot.
msg.req.robot_type = "NAO"
# Use DIJKSTRA algorithm
msg.req.algorithm = "dijkstra"

msg.req.pose_start = { 
    'header': {'seq': 0, 'stamp':{'sec': 0, 'nsecs': 0}, 'frame_id': '' },
    'pose': {
        'position': {'x': 10, 'y': 10, 'z': 20},
        'orientation': {'x': 0, 'y': 0, 'z': 0, 'w': 0}
    }
}

msg.req.pose_goal = { 
    'header': {'seq': 0, 'stamp':{'sec': 0, 'nsecs': 0}, 'frame_id': '' },
    'pose': {
        'position': {'x': 30, 'y': 10, 'z': 20},
        'orientation': {'x': 0, 'y': 0, 'z': 0, 'w': 0}
    }
}

response = svc.call(msg)
```


**Example output**:
```python
print response.plan_found
>> 0
print response.path
>> [ {POSE_1}, {POSE_2}, ... ]
print response.error
>> ""
```


***


## Path Planning - Upload Map

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Path-planner)


**Request object: PathPlanningUploadMap.Request**
```python
# The name of the map to store on the Platform
String map_name

# Path to the map image png file.
String png_file

# Path to the map description yaml file.
String yaml_file
```


**Response object: PathPlanningUploadMap.Response**
```python
# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import PathPlanningUploadMap
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = PathPlanningUploadMap()

# The map name
msg.req.map_name = "MAP_NAME"
# Path to the map png image gile
msg.req.png_file = "PATH"
# Path to the map yaml descriptor file
msg.req.yaml_file = "PATH"

response = svc.call(msg)
```


**Example output**:
```python
print response.error
>> ""
```


***


## Text To Speech

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Text-to-speech-using-Espeak-&-Mbrola)


**Request object: TextToSpeech.Request**
```python
# Input text to translate to audio data
String text

# Language to use for translation. Valid values are currently:  'el', 'en'
String language
```

**Response object: TextToSpeech.Response**
```python
# The audio data payload. Payload encoding is defined by the 'encoding' json field.
String/base64 payload

# Codec used to encode the audio data payload.
String encoding

# A static basename for the audio data file
String basename

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import TextToSpeech
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = TextToSpeech()
msg.req.text = "Robots are awesome"
msg.req.language = "en"

response = svc.call(msg)
```


**Example output**:
```python
print response.error
>> ""
print response.encoding
>> "base64"

if response.error is "":
    # Store audio data to file
    response.store_audio("/tmp/tts.wav")
```


***


## News Explorer

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-News-Explorer)


**Request object: NewsExplore.Request**
```python
# The news search engine to use.
String news_engine

# Desired keywords. Required!
Array keywords

# Reject list of previously read articles, in order to avoid duplicates.
Array exclude_titles

# Region.
String region

# Main topics, i.e. sports, politics, etc.
String topic

# Number of news stories.
Int num_news
```

**Response object: NewsExplore.Response**
```python
# Array of story objects, where story is of structure:
# { title: '', content: '', puplisher: '', publishedDate: '', url: '' }
Array news_stories

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import NewsExplore
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = NewsExplore()
msg.req.num_news = 2
msg.req.keywords = ['Thessaloniki']

response = svc.call(msg)
```


**Example output**:
```python
print response.news_stories
>> [ {STORY_1}, {STORY_2} ]
print response.error
>> ""
```



***


## Geolocation

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Geolocator)


**Request object: Geolocation.Request**
```python
# The ipv4 address
String ipaddr

# Engine to use. Defaults to 'ip-api' (Currently the only supported).
String engine
```

**Response object: Geolocation.Response**

```
# City location
String city

# Country location
String country

# Location country_code
String country_code

# The latitude
String latitude

# The longtitude
String longtitude

# Location region
String region

# Location timezone
String timezone

# Location zip-postal code
String zip

# Error message
String error
```


**Call example**:
```python
from RappCloud.CloudMsgs import Geolocation
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = Geolocation()
msg.req.ipaddr = "104.16.115.182"

response = svc.call(msg)
```


**Example output**:
```python
print response.country
>> "United States"
print response.region
>> "California"
print response.city
>> "San Francisco"
print response.country_core
>> "US"
print response.timezone
>> "America/Los_Angeles"
print response.zip
>> "94107"
print response.latitude
>> 37.76969909667969
print response.longtitude
>> -122.39330291748047
print response.error
>> ""
```

***


## User Personal Info

**Request object: UserPersonalInfo.Request**
```python
None
```

**Response object: UserPersonalInfo.Response**

```
# User's name
String name

# User's surname
String surname

# User's language
String language

# User's registered (to Platform db) destination email addresses
Array emails

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import UserPersonalInfo
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = UserPersonalInfo()
response = svc.call(msg)
```

**Example output**:
```python
print response.name
>> "rapp"
print response.surname
>> "rapp"
print response.language
>> "el"
print response.emails
>> [{u'email_address': u'rapp.friend@gmail.com', u'user': u'rappfriend'}, {u'email_address': u'rapp.friend2@gmail.com', u'user': u'rappfriend2'}]
print response.error
>> ""
```

