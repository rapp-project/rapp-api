- [Cloud Messages - General description](https://github.com/rapp-project/rapp-api/blob/python/python/RappCloud/CloudMsgs/README.md#cloud-messages)
- RAPP Platform API Python calls
  - [Face detection]()

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
***

## Face detection

**Description**: Performs face detection in an image

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
msg.imageFilepath = "PATH"
# If true, detection will take less time but it will be less accurate
msg.fast = True

response = svc.call(msg)
```

**Example output**:
```python
print response.faces
>> [ { up_left_point: {x: 0, y: 0}, down_right_point: {x: 100, y: 100} }  ... ]
print response.error
>> ""
```

***

## Qr detection

**Request object: QrDetection.Request**
```
# System path to the image file
String imageFilepath
```

**Response object: QrDetection.Response**
```
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
msg.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.qr_centers
>> [ {x: 0, y: 0}, {x: 100, y: 100}, ... ]
print response.qr_messages
>> [ 'test 1', 'test 2' ]
print response.error
>> ""
```

***

## Human detection

**Request object: HumanDetection.Request**
```
# System path to the image file
String imageFilepath
```

**Response object: HumanDetection.Response**
```
# Array of detected humans
# humans: [{<human_1>}, ..., {<human_n>}] where human_x is an object of structure:
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
msg.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.qr_centers
>> [ {up_left_point: {x: 0, y: 0}, down_right_point: {x: 100, y: 100} }, ... ]
print response.error
>> ""
```

## Hazard detection - Door

**Request object: HazardDetectionDoor.Request**
```
# System path to the image file
String imageFilepath
```

**Response object: HazardDetectionDoor.Response**
```
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
msg.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.door_angle
>> 0.83
print response.error
>> ""
```

## Hazard detection - Lights

**Request object: HazardDetectionLight.Request**
```
# System path to the image file
String imageFilepath
```

**Response object: HazardDetectionLight.Response**
```
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
msg.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.light_level
>> 0.83
print response.error
>> ""
```

## Object detection Caffe

**Request object: ObjectDetectionCaffe.Request**
```
# System path to the image file
String imageFilepath
```

**Response object: ObjectDetectionCaffe.Response**
```
# Recognized object class
String object_class

# Error message
String error
```

**Call example**:
```python
from RappCloud.CloudMsgs import ObjectDetectionCaffe
from RappCloud import RappPlatformService

svc = RappPlatformService()
msg = ObjectDetectionCaffe()

# System path to the image file
msg.imageFilepath = "PATH"

response = svc.call(msg)
```

**Example output**:
```python
print response.object_class
>> "television"
print response.error
>> ""
```

## Set Noise Profile

**Request object: SetNoiseProfile.Request**
```
# System path to the audio file
String audiofile

# Audio source type/format. e.g. "nao_wav_1_ch"
String audio_source
```

**Response object: SetNoiseProfile.Response**
```
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
msg.audiofile = "PATH"
# Audio source type/format. e.g. "nao_wav_1_ch"
msg.audio_source = "nao_wav_1_ch"

response = svc.call(msg)
```

**Example output**:
```python
print response.error
>> ""
```

## Speech Recognition Sphinx

**Request object: SpeechRecognitionSphinx.Request**

```
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
```
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
msg.audiofile = "PATH"
# Audio source type/format. e.g. "nao_wav_1_ch"
msg.audio_source = "nao_wav_1_ch"
# Language to use for speech recognition
msg.language = 'en'
# Array of words to recognize
msg.words = ['yes', 'no']
# Under consideration sentences
msg.sentences = msg.words
# Grammar to use
msg.grammar = []

response = svc.call(msg)
```

**Example output**:
```python
print response.words
>> ['yes']
print response.error
>> ""
```

## CloudMsgs/SpeechRecognitionGoogle Message

### File: RappCloud/CloudMsgs/SpeechRecognitionGoogle.py

### Request object: SpeechRecognitionGoogle.Request

```
# System path to the audio file
String audiofile

# Audio source type/format. e.g. "nao_wav_1_ch"
String audio_source

# Language to use for speech recognition
String language
```

### Response object: SpeechRecognitionGoogle.Response

```
# Recognized words with highest confidence
Array words

# Alternative sentences
Array sentences

# Error message
String error
```

## CloudMsgs/OntologySubclasses Message

### File: RappCloud/CloudMsgs/OntologySubclasses.py

### Request object: OntologySubclasses.Request

```
# The query to the ontology database
String query
```

### Response object: OntologySubclasses.Response

```
# Ontology query results.
Array results

# Error message
String error
```

## CloudMsgs/OntologySuperclasses Message

### File: RappCloud/CloudMsgs/OntologySuperclasses.py

### Request object: OntologySuperclasses.Request

```
# The query to the ontology database
String query
```

### Response object: OntologySuperclasses.Response

```
# Ontology query results.
Array results

# Error message
String error
```

## CloudMsgs/OntologyIsSubsuperclass Message

### File: RappCloud/CloudMsgs/OntologyIsSubsuperclass.py

### Request object: OntologyIsSubsuperclass.Request

```
# The parent class
String parent_class

# The child class
String child_class

# Recursive search
Bool recursive
```

### Response object: OntologyIsSubsuperclass.Response

```
# Ontology query result.
Bool result

# Error message
String error
```

## CloudMsgs/CognitiveExerciseSelect Message

### File: RappCloud/CloudMsgs/CognitiveExerciseSelect.py

### Request object: CognitiveExerciseSelect.Request

```
# Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
# https://github.com/rapp-project/rapp-platform/tree/master/rapp_cognitive_exercise
String test_type

# Force select exercise from this subtype. Depends on test_type value
String test_subtype

# Force select exercise from this difficulty. Depends on test_type and test_subtype values
String test_diff

# Force select exercise index. Depends on test_type, test_subtype and test_diff values
String test_index
```

### Response object: CognitiveExerciseSelect.Response

```
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

## CloudMsgs/CognitiveGetHistory Message

### File: RappCloud/CloudMsgs/CognitiveGetHistory.py

### Request object: CognitiveGetHistory.Request

```
# Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
# https://github.com/rapp-project/rapp-platform/tree/master/rapp_cognitive_exercise
String test_type

# Unix timestamp
Int time_from

# Unix timestamp
Int time_to
```

### Response object: CognitiveGetHistory.Response

```
# History records
Dict records

# Error message
String error
```

## CloudMsgs/CognitiveGetScores Message

### File: RappCloud/CloudMsgs/CognitiveGetScores.py

### Request object: CognitiveGetScores.Request

```
# Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
# https://github.com/rapp-project/rapp-platform/tree/master/rapp_cognitive_exercise
String test_type

# Unix timestamp
Int time_to
```

### Response object: CognitiveGetScores.Response

```
# Test classes indexes
Array test_classes

# Scores. Each array index corresponds to the test class in test_classes
Array scores

# Error message
String error
```

## CloudMsgs/CognitiveRecordPerformance Message

### File: RappCloud/CloudMsgs/CognitiveRecordPerformance.py

### Request object: CognitiveRecordPerformance.Request

```
# The exercise test instance name (Returned by CognitiveExerciseSelect)
String test_instance

# Performance score to record
Int score
```

### Response object: CognitiveRecordPerformance.Response

```
# Cognitive exercise performance entry in ontology.
String performance_entry

# Error message
String error
```

## CloudMsgs/EmailFetch Message

### File: RappCloud/CloudMsgs/EmailFetch.py

### Request object: EmailFetch.Request

```
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

### Response object: EmailFetch.Response

```
# Array of emailEntry objects, where emailEntry is of structure:
# { sender: '', receivers: [], body: '', date: '', body: '', attachments: [] }
Array emails

# Error message
String error
```

## CloudMsgs/EmailSend Message

### File: RappCloud/CloudMsgs/EmailSend.py

### Request object: EmailSend.Request

```
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

### Response object: EmailSend.Response

```
# Error message
String error
```

## CloudMsgs/WeatherReportCurrent Message

### File: RappCloud/CloudMsgs/WeatherReportCurrent.py

### Request object: WeatherReportCurrent.Request

```
# The desired city
String city

# The weather API to use. Defaults to "yweather" .
String weather_reporter

# The return value units.
Int metric
```

### Response object: WeatherReportCurrent.Response

```
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

## CloudMsgs/WeatherReportForecast Message

### File: RappCloud/CloudMsgs/WeatherReportForecast.py

### Request object: WeatherReportForecast.Request

```
# The desired city
String city

# The weather API to use. Defaults to "yweather" .
String weather_reporter

# The return value units.
Int metric
```

### Response object: WeatherReportForecast.Response

```
# Array of forecastEntry objects, where forecastEntry is of structure:
# { high_temp: '', low_temp: '', description: '', date: '' }
Array forecast

# Error message
String error
```

## CloudMsgs/PathPlanningPlan2D Message

### File: RappCloud/CloudMsgs/PathPlanningPlan2D.py

### Request object: PathPlanningPlan2D.Request

```
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

### Response object: PathPlanningPlan2D.Response

```
# Plan status (https://github.com/rapp-project/rapp-platform/tree/master/rapp_path_planning/rapp_path_planning)
Int plan_found

# Ff plan_found is equal to 0 (path found), this is an array of waypoints from start to goal.
Array path

# Error message
String error
```

## CloudMsgs/PathPlanningUploadMap Message

### File: RappCloud/CloudMsgs/PathPlanningUploadMap.py

### Request object: PathPlanningUploadMap.Request

```
# The name of the map to store on the Platform
String map_name

# Path to the map image png file.
String png_file

# Path to the map description yaml file.
String yaml_file
```

### Response object: PathPlanningUploadMap.Response

```
# Error message
String error
```

## CloudMsgs/TextToSpeech Message

### File: RappCloud/CloudMsgs/TextToSpeech.py

### Request object: TextToSpeech.Request

```
# Input text to translate to audio data
String text

# Language to use for translation. Valid values are currently:  'el', 'en'
String language
```

### Response object: TextToSpeech.Response

```
# The audio data payload. Payload encoding is defined by the 'encoding' json field.
String/base64 payload

# Codec used to encode the audio data payload.
String encoding

# A static basename for the audio data file
String basename

# Error message
String error
```

## CloudMsgs/NewsExplore Message

### File: RappCloud/CloudMsgs/NewsExplore.py

### Request object: NewsExplore.Request

```
# The news search engine to use.
String news_engine

# Desired keywords.
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

### Response object: NewsExplore.Response

```
# Array of story objects, where story is of structure:
# { title: '', content: '', puplisher: '', publishedDate: '', url: '' }
Array news_stories

# Error message
String error
```

## CloudMsgs/Geolocation Message

### File: RappCloud/CloudMsgs/Geolocation.py

### Request object: Geolocation.Request

```
# The ipv4 address
String ipaddr

# Engine to use. Defaults to 'ip-api' (Currently the only supported).
String engine
```

### Response object: Geolocation.Response

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

