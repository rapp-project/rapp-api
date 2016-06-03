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

## Face detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Face-Detection)

**Sample call** ```faceDetection(imageFilepath, fast)```

**Input arguments**
- ```String imageFilepath```: System path to the image file
- ```Bool fast```: If true, detection will take less time but it will be less accurate

**Return values**
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
from RappCloud import RappPlatformAPI

ch = RappPlatformAPI()

response = ch.faceDetection("PATH", False)
```

**Example output**:
```python
print response
>> {'error': u'', 'faces': [{u'up_left_point': {u'y': 246.0, u'x': 658.0}, u'down_right_point': {u'y': 375.0, u'x': 787.0}}]}
```
***

## Qr detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-QR-Detection)

**Sample call** ```qrDetection(imageFilepath)```

**Input arguments**
- ```String imageFilepath```: System path to the image file

**Return values**
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
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.qrDetection("PATH")
```

**Example output**:
```python
print response
>> {'qr_messages': [u'rapp project qr sample'], 'qr_centers': [{u'y': 165.0, u'x': 165.0}], 'error': u''}
```

***

## Human detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Human-Detection)

**Sample call** ```humanDetection(imageFilepath)```

**Input arguments**
- ```String imageFilepath```: System path to the image file

**Return values**
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
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.humanDetection("PATH")
```

**Example output**:
```python
print response
>> {'humans': [{u'up_left_point': {u'y': 34.0, u'x': 48.0}, u'down_right_point': {u'y': 402.0, u'x': 232.0}}, {u'up_left_point': {u'y': 13.0, u'x': 494.0}, u'down_right_point': {u'y': 893.0, u'x': 934.0}}], 'error': u''}
```

***

## Hazard detection - Door

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Hazard-Detection)

**Sample call** ```hazardDetectionDoor(imageFilepath)```

**Input arguments**
- ```String imageFilepath```: System path to the image file

**Return values**
```python
# The angle of the detected open door
Float door_angle

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.hazardDetectionDoor("PATH")
```

**Example output**:
```python
print response
>> {'door_angle': 6, 'error': u''}
```

***

## Hazard detection - Lights

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Hazard-Detection)

**Sample call** ```hazardDetectionLights(imageFilepath)```

**Input arguments**
- ```String imageFilepath```: System path to the image file

**Return values**
```python
# The, detected on the image frame, light level.
Float light_level

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.hazardDetectionLights("PATH")
```

**Example output**:
```python
print response
>> {'light_level': 100, 'error': u''}
```

***

## Object recognition Caffe

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Caffe-Wrapper)

**Sample call** ```objectRecognitionCaffe(imageFilepath)```

**Input arguments**
- ```String imageFilepath```: System path to the image file

**Return values**
```python
# Recognized object class
String object_class

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.objectRecognitionCaffe("PATH")
```

**Example output**:
```python
print response
>> {'object_class': u'boa constrictor, Constrictor constrictor', 'error': u''}
```

***

## Set Noise Profile

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Audio-Processing)

**Sample call** ```setNoiseProfile(audiofile, audio_source)```

**Input arguments**
- ```String audiofile```: System path to the audio file
- ```String audio_source```: Audio source type/format. e.g. "nao_wav_1_ch"

**Return values**
```python
# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.objectRecognitionCaffe("PATH", "nao_wav_1_ch")
```

**Example output**:
```python
print response
>> {"error": ""}
```

***

## Speech Recognition Sphinx

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Speech-Detection-using-Sphinx4)

**Sample call** ```speechRecognitionSphinx(audiofile, audio_source, language, words, sentences, grammar)```

**Input arguments**
- ```String audiofile```: System path to the audio file
- ```String audio_source```: Audio source type/format. e.g. "nao_wav_1_ch"
- ```String language```: Language to use for speech recognition
- ```Array words```: Array of words to recognize
- ```Array sentences```: Under consideration sentences
- ```Array grammar```: Grammar to use

**Return values**
```python
# Recognized words
Array words

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.speechRecognitionSphinx("PATH", "nao_wav_1_ch", 'en', ['yes', 'no'], ['yes', 'no'], [])
```

**Example output**:
```python
print response
>> {'words': [u'no', u'no', u'yes'], 'error': u''}
```

***

## Speech Recognition Google 

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Speech-Detection-using-Google-API)

**Sample call** ```speechRecognitionGoogle(audiofile, audio_source, language)```

**Input arguments**
- ```String audiofile```: System path to the audio file
- ```String audio_source```: Audio source type/format. e.g. "nao_wav_1_ch"
- ```String language```: Language to use for speech recognition

**Return values**

```py
# Recognized words with highest confidence
Array words

# Alternative sentences
Array sentences

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.speechRecognitionGoogle("PATH", "nao_wav_1_ch", 'en')
```

**Example output**:
```python
print response
>> {'error': u'', 'words': [u'map'], 'sentences': [[u'math'], [u'mark'], [u'Mass']]}
```

***

## Ontology Query - Subclasses of

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Knowrob-wrapper)

**Sample call** ```ontologySubclasses(ontology_class, recursive)```

**Input arguments**
- ```String ontology_class```: The query to the ontology database
- ```Bool recursive```: Recursive search

**Return values**

```py
# Ontology query results.
Array results

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.ontologySubclasses("Oven", False)
```

**Example output**:
```python
print response
>> {'results': [u'http://knowrob.org/kb/knowrob.owl#MicrowaveOven', u'http://knowrob.org/kb/knowrob.owl#RegularOven', u'http://knowrob.org/kb/knowrob.owl#ToasterOven'], 'error': u''}
```

***

## Ontology Query - Superclasses of

**Description [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Knowrob-wrapper)**

**Sample call** ```ontologySuperclasses(ontology_class, recursive)```

**Input arguments**
- ```String ontology_class```: The query to the ontology database
- ```Bool recursive```: Recursive search

**Return values**

```python
# Ontology query results.
Array results

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.ontologySuperclasses("Oven", False)
```

**Example output**:
```python
print response
>> {'results': [u'http://knowrob.org/kb/knowrob.owl#Box-Container', u'http://knowrob.org/kb/knowrob.owl#FurniturePiece', u'http://knowrob.org/kb/knowrob.owl#HeatingDevice', u'http://knowrob.org/kb/knowrob.owl#HouseholdAppliance'], 'error': u''}
```

***

## Ontology Query - Is Subsuperclass of

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Knowrob-wrapper)

**Sample call** ```ontologyIsSubsuperclass(parent_class, child_class, recursive)```

**Input arguments**
- ```String parent_class```: The parent class
- ```String child_class```: The child class
- ```Bool recursive```: Recursive search

**Return values**

```python
# Ontology query result.
Bool result

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.ontologyIsSubsuperclass("Oven", "Microwave", False)
```

**Example output**:
```python
print response
>> {'result': False, 'error': u''}
```

***

## Cognitive Exercises - Test Selector

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Sample call** ```cognitiveExerciseSelect(test_type, test_subtype, test_diff, test_index)```

**Input arguments**
- ```String test_type```: Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
- ```String test_subtype```: Force select exercise from this subtype. Depends on test_type value
- ```String test_diff```: Force select exercise from this difficulty. Depends on test_type and test_subtype values
- ```String test_index```: Force select exercise index. Depends on test_type, test_subtype and test_diff values

**Return values**
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
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.cognitiveExerciseSelect('ArithmeticCts', 'TransactionChangeCts', '1', '1')
```

**Example output**:
```python
print response
>> {'error': u'', 'test_type': u'ArithmeticCts', 'possib_ans': [[u'\u03ad\u03bd\u03b1 \u03b5\u03c5\u03c1\u03ce \u03ba\u03b1\u03b9 \u03b5\u03af\u03ba\u03bf\u03c3\u03b9 \u03bb\u03b5\u03c0\u03c4\u03ac', u'\u03b4\u03cd\u03bf \u03b5\u03c5\u03c1\u03ce \u03ba\u03b1\u03b9 \u03b4\u03ad\u03ba\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac', u'\u03ad\u03bd\u03b1 \u03b5\u03c5\u03c1\u03ce \u03ba\u03b1\u03b9 \u03c3\u03b1\u03c1\u03ac\u03bd\u03c4\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac', u'\u03b5\u03be\u03ae\u03bd\u03c4\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac'], [u'\u03ad\u03bd\u03b1 \u03b5\u03c5\u03c1\u03ce \u03ba\u03b1\u03b9 \u03c0\u03ad\u03bd\u03c4\u03b5 \u03bb\u03b5\u03c0\u03c4\u03ac', u'\u03b4\u03cd\u03bf \u03b5\u03c5\u03c1\u03ce \u03ba\u03b1\u03b9 \u03b5\u03bd\u03b5\u03bd\u03ae\u03bd\u03c4\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac', u'\u03ad\u03bd\u03b1 \u03b5\u03c5\u03c1\u03ce \u03ba\u03b1\u03b9 \u03b5\u03bd\u03b5\u03bd\u03ae\u03bd\u03c4\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac', u'\u03b5\u03bd\u03b5\u03bd\u03ae\u03bd\u03c4\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac']], 'test_subtype': u'TransactionChangeCts', 'correct_ans': [u'\u03ad\u03bd\u03b1 \u03b5\u03c5\u03c1\u03ce \u03ba\u03b1\u03b9 \u03c3\u03b1\u03c1\u03ac\u03bd\u03c4\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac', u'\u03b5\u03bd\u03b5\u03bd\u03ae\u03bd\u03c4\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac'], 'questions': [u'\u0391\u03b3\u03bf\u03c1\u03ac\u03b6\u03bf\u03c5\u03bc\u03b5 \u03ad\u03bd\u03b1 \u03c8\u03c9\u03bc\u03af \u03c0\u03bf\u03c5 \u03ba\u03ac\u03bd\u03b5\u03b9 \u03b5\u03be\u03ae\u03bd\u03c4\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac; \u03ba\u03b1\u03b9 \u03b4\u03af\u03bd\u03bf\u03c5\u03bc\u03b5; \u03ad\u03bd\u03b1 \u03ba\u03ad\u03c1\u03bc\u03b1 \u03c4\u03c9\u03bd \u03b4\u03cd\u03bf \u03b5\u03c5\u03c1\u03ce. \u03a0\u03cc\u03c3\u03b1 \u03c1\u03ad\u03c3\u03c4\u03b1 \u03b8\u03b1 \u03bc\u03b1\u03c2 \u03b4\u03ce\u03c3\u03b5\u03b9 \u03bf \u03c6\u03bf\u03cd\u03c1\u03bd\u03b1\u03c1\u03b7\u03c2;', u'\u0391\u03b3\u03bf\u03c1\u03ac\u03b6\u03bf\u03c5\u03bc\u03b5 \u03ad\u03bd\u03b1 \u03b3\u03ac\u03bb\u03b1 \u03c0\u03bf\u03c5 \u03ba\u03ac\u03bd\u03b5\u03b9 \u03ad\u03bd\u03b1 \u03b5\u03c5\u03c1\u03ce \u03ba\u03b1\u03b9 \u03b4\u03ad\u03ba\u03b1 \u03bb\u03b5\u03c0\u03c4\u03ac; \u03ba\u03b1\u03b9 \u03b4\u03af\u03bd\u03bf\u03c5\u03bc\u03b5; \u03ad\u03bd\u03b1 \u03ba\u03ad\u03c1\u03bc\u03b1 \u03c4\u03c9\u03bd \u03b4\u03cd\u03bf \u03b5\u03c5\u03c1\u03ce. \u03a0\u03cc\u03c3\u03b1 \u03c1\u03ad\u03c3\u03c4\u03b1 \u03b8\u03b1 \u03c0\u03ac\u03c1\u03bf\u03c5\u03bc\u03b5 \u03c0\u03af\u03c3\u03c9;'], 'test_instance': u'ArithmeticCts_rMsqkRjP'}
```

(This response is in Greek)

***

## Cognitive Exercises - Get History Records

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Sample call** ```cognitiveGetHistory(test_type, time_from, time_to)```

**Input arguments**
- ```String test_type```: Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
- ```Int time_from```: Unix timestamp
- ```Int time_to```: Unix timestamp

**Return values**
```python
# History records
Dict records

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.cognitiveGetHistory('ArithmeticCts', 0, 1000000000000)
```

**Example output**:
```python
print response
>> {'records': {u'arithmeticcts': [{u'difficulty': u'1', u'timestamp': 1462879489, u'subtype': u'BasicArithmeticCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_bneXbLGX', u'type': u'ArithmeticCts'}, {u'difficulty': u'1', u'timestamp': 1462013618, u'subtype': u'BasicArithmeticCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_bneXbLGX', u'type': u'ArithmeticCts'}, {u'difficulty': u'1', u'timestamp': 1462013549, u'subtype': u'BasicArithmeticCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_bneXbLGX', u'type': u'ArithmeticCts'}, {u'difficulty': u'1', u'timestamp': 1462013438, u'subtype': u'BasicArithmeticCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_bneXbLGX', u'type': u'ArithmeticCts'}, {u'difficulty': u'1', u'timestamp': 1462013368, u'subtype': u'BasicArithmeticCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_bneXbLGX', u'type': u'ArithmeticCts'}, {u'difficulty': u'1', u'timestamp': 1462013331, u'subtype': u'BasicArithmeticCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_bneXbLGX', u'type': u'ArithmeticCts'}, {u'difficulty': u'1', u'timestamp': 1461861426, u'subtype': u'BasicArithmeticCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_bneXbLGX', u'type': u'ArithmeticCts'}, {u'difficulty': u'1', u'timestamp': 1461861382, u'subtype': u'BasicArithmeticCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_bneXbLGX', u'type': u'ArithmeticCts'}, {u'difficulty': u'2', u'timestamp': 1461861365, u'subtype': u'TimeDifferenceCts', u'score': 10, u'meanScoreForTypeUpToNow': 10.0, u'test': u'ArithmeticCts_ThPDDeBB', u'type': u'ArithmeticCts'}]}, 'error': u''}
```

***

## Cognitive Exercises - Get Scores

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Sample call** ```cognitiveGetScores(test_type, time_to)```

**Input arguments**
- ```String test_type```: Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts')
- ```Int time_to```: Unix timestamp

**Return values**
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
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.cognitiveGetScores('ArithmeticCts', 1000000000000)
```

**Example output**:
```python
print response
>> {'error': u'', 'test_classes': [u'ArithmeticCts'], 'scores': [10.0]}
```

***

## Cognitive Exercises - Record Performance

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Sample call** ```cognitiveGetScores(test_type, time_to)```

**Input arguments**
- ```String test_instance```: The exercise test instance name (Returned by CognitiveExerciseSelect)
- ```Int score```: The score (from 0.0 - 10.0)

**Return values**

```
# Cognitive exercise performance entry in ontology.
String performance_entry

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.cognitiveRecordPerformance('ArithmeticCts_rMsqkRjP', 10.0)
```

**Example output**:
```python
print response
>> {'performance_entry': u'http://knowrob.org/kb/knowrob.owl#CognitiveTestPerformed_MewmmEsP', 'error': u''}
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


