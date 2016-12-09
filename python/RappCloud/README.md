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

## Face detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Face-Detection)

**Sample call** ```faceDetection(imageFilepath, fast)```

**Input arguments**
- ```String imageFilepath```: System path to the image file
- ```Bool fast```: If true, detection will take less time but it will be less accurate. The default value is False

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
- ```Array sentences```: Under consideration sentences. Default value is ```[]```, meaning that it will take the same values as ```words```
- ```Array grammar```: Grammar to use. Default value is ```[]```

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

response = ch.speechRecognitionSphinx("PATH", "nao_wav_1_ch", 'en', ['yes', 'no'])
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
- ```Bool recursive```: Recursive search. Default value is ```False```

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

response = ch.ontologySubclasses("Oven")
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
- ```Bool recursive```: Recursive search. Default value is ```False```

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

response = ch.ontologySuperclasses("Oven")
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
- ```Bool recursive```: Recursive search. Default value is ```False```

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

If any of the parameters is not provided, the algorithm will select a test among all the available values of this parameter.

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
# Alternatively: response = ch.cognitiveExerciseSelect()
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
- ```String test_type```: Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts'). If not provided history from all classes is returned
- ```Int time_from```: Unix timestamp
- ```Int time_to```: Unix timestamp

If no times are provided all recorded history values are returned.

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
- ```String test_type```: Cognitive Exercise type. ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts'). If this parameter is not provided, scores from all types are returned.
- ```Int time_to```: Unix timestamp. If this parameter is not provided, scores till the present time are returned.

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

**Sample call** ```emailFetch(email, password, server, port, date_from, date_to, email_status, num_emails)```

**Input arguments**
- ```String email```: Email account username
- ```String password```: Email account password
- ```String server```: The email server imap address, i.e. 'imap.gmail.com'.
- ```String port```: The email server imap port. Leave empty to use default value.
- ```Int date_from```: Emails since date. Unix timestamp.
- ```Int date_do```: Emails until date. Unix timestamp.
- ```String email_status```: Define which mails the users requests. Values: ALL, UNSEEN. If not given, default value is UNSEEN
- ```Int num_emails```: Number of emails to fetch. If not provided, default number is 1.

**Return values**
```python
# Array of emailEntry objects, where emailEntry is of structure:
# { sender: '', receivers: [], date: '', body: '', attachments: [] }
Array emails

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.emailFetch('your.mail@gmail.com', 'your-password', 'imap.gmail.com', '993', 0, 100000000, 'ALL', 1)
```

**Example output**:
```python
print response
>> {'emails': [{u'body': u'', u'sender': u'Gitter Notifications <support@gitter.im>', u'attachments': [], u'receivers': [u'<your.mail@gmail.com>'], u'date': u'Fri, 03 Jun 2016 09:36:02 +0000', u'subject': u'Unread messages from someone'}], 'error': u''}
```

***

## Email - Send

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Email)

**Sample call** ```emailSend(email, password, server, port, recipients, body, subject, attach_file)```

**Input arguments**
- ```String email```: Email account username
- ```String password```: Email account password
- ```String server```: The email server imap address, i.e. 'imap.gmail.com'.
- ```String port```: The email server imap port. Leave empty to use default value.
- ```Array recipients```: Email addresses of the recipients
- ```String body```: Email body content
- ```String subject```: Email subject
- ```String attach_file```: Attachment file path. Can be a .zip file that will be decompressed on the server. If not set, no attachment is included.

**Return values**

```python
# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.emailSend('your.mail@gmail.com', 'your-password', 'imap.gmail.com', '993', ['another.mail@gmail.com'], 'This is the body', 'This is the subject', '~/attachment.zip')
```

**Example output**:
```python
print response
>> {'error': u''}
```

***

## Weather Reporter - Current Weather

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Weather-Reporter)

**Sample call** ```weatherReportCurrent(city, weather_reporter, metric)```

**Input arguments**
- ```String city```: The desired city
- ```String weather_reporter```: The weather API to use. Defaults to "forecast.io" .
- ```Int metric```: The return value units (0 for metric [default], 1 for US units)

**Return values**
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
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.weatherReportCurrent('Athens', '', 0)
# Alternatively response = ch.weatherReportCurrent('Athens')
```

**Example output**:
```python
print response
>> {'wind_speed': u'1.64', 'pressure': u'1016.45', 'temperature': u'67.78', 'error': '', 'date': u'1464948878', 'wind_temperature': u'', 'weather_description': u'Clear', 'wind_direction': u'', 'visibility': u'8.76', 'humidity': u'0.93'}
```

## Weather Reporter - Forecast

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Weather-Reporter)

**Sample call** ```weatherReportForecast(city, weather_reporter, metric)```

**Input arguments**
- ```String city```: The desired city
- ```String weather_reporter```: The weather API to use. Defaults to "forecast.io" .
- ```Int metric```: The return value units (0 for metric [default], 1 for US units)

**Return values**
```
# Array of forecastEntry objects, where forecastEntry is of structure:
# { high_temp: '', low_temp: '', description: '', date: '' }
Array forecast

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.weatherReportForecast('Athens', 'forecast.io', 0)
# Alternatively response = ch.weatherReportForecast('Athens')
```

**Example output**:
```python
print response
>> {'error': u'', 'forecast': [{u'high_temp': u'96.11', u'date': u'1465531200', u'low_temp': u'70.02', u'description': u'Clear throughout the day.'}, {u'high_temp': u'92.93', u'date': u'1464926400', u'low_temp': u'67.69', u'description': u'Partly cloudy starting in the afternoon.'}, {u'high_temp': u'92.21', u'date': u'1465012800', u'low_temp': u'68.2', u'description': u'Light rain starting in the afternoon.'}, {u'high_temp': u'83.84', u'date': u'1465099200', u'low_temp': u'71.84', u'description': u'Light rain throughout the day.'}, {u'high_temp': u'87.86', u'date': u'1465185600', u'low_temp': u'67.49', u'description': u'Drizzle in the evening.'}, {u'high_temp': u'90.3', u'date': u'1465272000', u'low_temp': u'62.76', u'description': u'Clear throughout the day.'}, {u'high_temp': u'91.22', u'date': u'1465358400', u'low_temp': u'63.75', u'description': u'Clear throughout the day.'}, {u'high_temp': u'92.09', u'date': u'1465444800', u'low_temp': u'62.35', u'description': u'Clear throughout the day.'}]}
```

***

## Path Planning - Plan Path 2D

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Path-planner)

**Sample call** ```pathPlanningPlan2D(map_name, robot_type, pose_start, pose_goal, algorithm)```

**Input arguments**
- ```String map_name```: The name of the, stored to the Platform, map
- ```String robot_type```: The robot type. It is required to determine it's parameters (footprint etc.)
- ```Dict pose_start```: Start pose of the robot. Same structure to ROS-GeometryMsgs/PoseStamped
- ```Dict pose_goal```: Goal pose of the robot. Same structure to ROS-GeometryMsgs/PoseStamped
- ```String algorithm```: The path planning algorithm to apply. If not set, default value is ```dijkstra```

**Return values**
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
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.pathPlanningPlan2D('Map_Name', "NAO", "dijkstra", {'pose': {'position': {'x': 1, 'y': 1, 'z': 0}, 'orientation': {'x': 0, 'y': 0, 'z': 0, 'w': 0}}}, {'pose': {'position': {'x': 1.2, 'y': 1, 'z': 0}, 'orientation': {'x': 0, 'y': 0, 'z': 0, 'w': 0}}})
```

**Example output**:
```python
print response
>> {'path': [{u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 0.9999999776482582, u'x': 0.9999999776482582, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.17576372515799546, u'w': 0.9844323810798712}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0046011890932647, u'x': 1.0124746477795838, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.3062984133859556, u'w': 0.9519355450644997}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0104327166728808, u'x': 1.020598274306991, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.28376745671677717, u'w': 0.9588931277824928}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0158747636703822, u'x': 1.0289877852278693, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.23880056355794518, u'w': 0.9710686334365907}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0205125962083201, u'x': 1.0378472668413679, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.21960181069564919, u'w': 0.9755895882691616}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0247974166691876, u'x': 1.0468827585827682, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.18827274545607756, u'w': 0.9821167819146718}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0284955367037156, u'x': 1.0561738350352528, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.16860828328083796, u'w': 0.9856831371232282}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0318194349448504, u'x': 1.0656052923439745, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.1368821414059984, u'w': 0.9905873406035978}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0345313031703682, u'x': 1.0752305362694585, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.11778258630324452, u'w': 0.9930394062491774}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0368705517753085, u'x': 1.0849530549730417, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.10125460964580843, u'w': 0.9948605450139607}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0388852459441438, u'x': 1.0947480529230518, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.07479851379405521, u'w': 0.9971986674350305}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0403770214234953, u'x': 1.1046361294842626, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.06663824995713166, u'w': 0.9977772014045274}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0417068248605688, u'x': 1.1145473231103864, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.02074881326706693, u'w': 0.9997847202013084}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0421217113259047, u'x': 1.1245387016712414, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.02418837385898944, u'w': 0.9997074184830569}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0416380840173787, u'x': 1.134527028474352, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.07344865953899535, u'w': 0.997298999504123}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0401730877122333, u'x': 1.1444190723206304, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.16801841321736974, u'w': 0.9857838570497679}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0368604809747524, u'x': 1.1538544969144198, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.19167569518739944, u'w': 0.9814583169317111}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0330980451457634, u'x': 1.1631197097200214, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.2587691113577832, u'w': 0.9659392046123313}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0280989607848454, u'x': 1.1717804456104233, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.31072885466880645, u'w': 0.9504985948838703}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0221919784950018, u'x': 1.1798494456742077, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.38013257726865324, u'w': 0.9249320103116182}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.01516004200667, u'x': 1.1869594308668496, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.4247807218671594, u'w': 0.9052962710240305}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0074690021395156, u'x': 1.1933506508167682, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': -0.40930865362813246, u'w': 0.9123959809562543}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93018853}, u'frame_id': u'map', u'seq': 0}, u'pose': {u'position': {u'y': 0.9999999776482582, u'x': 1.1999999731779099, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.3404252641358363, u'w': 0.9402715775445124}}}, {u'header': {u'stamp': {u'secs': 1464949299, u'nsecs': 93044905}, u'frame_id': u'/map', u'seq': 0}, u'pose': {u'position': {u'y': 1.0, u'x': 1.2, u'z': 0.0}, u'orientation': {u'y': 0.0, u'x': 0.0, u'z': 0.0, u'w': 0.0}}}], 'plan_found': 1, 'error': u''}
```

***

## Path Planning - Upload Map

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Path-planner)

**Sample call** ```pathPlanningPlan2D(map_name, robot_type, algorithm, pose_start, pose_goal)```

**Input arguments**
- ```String map_name```: The name of the map to store on the Platform
- ```String png_file```: Path to the map image png file.
- ```String yaml_file```: Path to the map description yaml file.

**Return values**
```python
# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.pathPlanningUploadMap('Map_Name', '~/map.png', '~/map_yaml.yaml')
```

**Example output**:
```python
print response
>> {'error': u''}
```

***

## Text To Speech

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Text-to-speech-using-Espeak-&-Mbrola)

**Sample call** ```textToSpeech(text, language, audio_file)```

**Input arguments**
- ```String text```: Input text to translate to audio data
- ```String language```: Language to use for translation. Valid values are currently:  'el', 'en'
- ```String audio_file```: The audio file to write to

**Return values**
```python
# Codec used to encode the audio data payload.
String encoding

# A static basename for the audio data file
String basename

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.textToSpeech('Hello there', 'en', 'PATH_FOR_FILE')
```

**Example output**:
```python
print response
>> {'basename': u'tts_RTC9L.wav', 'error': u'', 'encoding': u'base64'}
```

***

## News Explorer

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-News-Explorer)

**Sample call** ```newsExplore(news_engine, keywords, exclude_titles, region, topic, num_news)```

**Input arguments**
- ```Array keywords```: Desired keywords. Required!
- ```String region```: Region (not required - empty by default).
- ```String topic```: Main topics, i.e. sports, politics, etc (not required - empty by default)
- ```String news_engine```: The news search engine to use. If not set, default value is ```eventregistry```
- ```Int num_news```: Number of news stories. If not set, default value is 1.
- ```Array exclude_titles```: Reject list of previously read articles, in order to avoid duplicates. If not set, default value is ```[]```.

**Return values**
```python
# Array of story objects, where story is of structure:
# { title: '', content: '', puplisher: '', publishedDate: '', url: '' }
Array news_stories

# Error message
String error
```

**Call example**:
```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.newsExplore('', ['Greece', 'football'], '', '', 1)
# Alternatively response = ch.newsExplore(['Greece', 'football'])
```

**Example output**:
```python
print response
>> {'error': u'', 'news_stories': [{u'content': u"With a team ethic built on discipline plus a strong defence, Romania bear more than a passing resemblance to the Greece team which sprang out of nowhere to win Euro 2004.\n\nWhile few observers expect Anghel Iordanescu's side to emulate that success, their ability to prevent other teams scoring ...", u'publisher': u'RTE.ie', u'title': u'Romania aiming to emulate Greek class of 2004', u'url': u'http://www.rte.ie/sport/soccer/2016/0603/793062-romania-aiming-to-emulate-greek-champions/', u'publishedDate': u'2016-06-03'}]}
```

***

## Geolocation

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Geolocator)

**Sample call** ```geolocation(ipaddr, engine)```

**Input arguments**
- ```String ipaddr```: The ipv4 address
- ```String engine```: Engine to use. Defaults to 'ip-api' (Currently the only supported).

**Return value**

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
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.geolocation('155.207.33.163')
```

**Example output**:
```python
print response
>> {'city': u'Thessaloniki', 'zip': u'', 'country_code': u'GR', 'timezone': u'Europe/Athens', 'latitude': 40.64030075073242, 'country': u'Greece', 'region': u'Central Macedonia', 'error': u'', 'longtitude': 22.943899154663086}
```


## User Personal Info

**Sample call** ```userPersonalInfo()```

**Input arguments**
None

**Return value**

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
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.userPersonalInfo()
```

**Example output**:
```python
print response
>> {'error': u'', 'surname': u'nosurname', 'emails': [{u'email_address': u'rapp.friend@gmail.com', u'user': u'rappfriend'}, {u'email_address': u'rapp.friend2@gmail.com', u'user': u'rappfriend2'}], 'language': u'el', 'name': u'noname'}
```
