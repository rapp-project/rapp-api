# JS DOCUMENTATION
-----------------------

- JS API cloud classes
  - [Available Services](#available-services)
  - [Cognitive Exercices](#cognitive-exercises)
    - [Test Selector](#cognitive-test-selector)
    - [Record Performance](#cognitive-record-performance)
    - [Get History](#cognitive-get-history)
    - [Get Scores](#cognitive-get-scores)
  - [Email](#email)
    - [Fetch email](#email-fetch)
    - [Send email](#email-send)
  - [Geolocation](#geolocation)
  - [News](#news)
  - [Ontology](#ontology)
    - [Subclasses of](#ontology-subclasses-of)
    - [Superclasses of](#ontology-superclasses-of)
    - [Is Subclass Superclass of](#ontology-is-subsuperclass-of)
  - [Path Planning](#path-planning)
    - [Path Plan 2D](#path-planning-2d) 
    - [Path Upload Map](#path-upload-map)
  - [Speech Services](#speech-services)
    - [Google S2T](#speech-google)
    - [CMU Sphinx S2T](#speech-cmu-sphinx4)
    - [Set Noise](#set-noise)
    - [Text to Speech](#text-to-speech)
  - [Vision Services](#vision-services)
    - [Door Angle Detection](#vision-door-angle)
    - [Face Detection](#vision-face-detect)
    - [Human Detection](#vision-human-detect)
    - [Light Detection](#vision-light-detect)
    - [QR Code Detection](#vision-qrcode-detect)
    - [Object Recognition](#vision-object-recognition)
    - [Object Detection Learn Object](#vision-object-detection-learn-object)
    - [Object Detection Clear Models](#vision-object-detection-clear-models)
    - [Object Detection Load Models](#vision-object-detection-load-models)
    - [Object Detection Find Objects](#vision-object-detection-find-objects)
  - [Weather](#weather)
    - [Current Report](#weather-report-current)
- JS API object classes
  - [Face](#face)
  - [Human](#human)

## Available Services
Method `RAPPCloud.prototype.available_services` in `rapp-api/js/includes/cloud/available_services.js`.
A cloud call which will return a list of pairs of strings, the first string representing the service name and the second defining the URL.

**Input arguments**
- `callback` : (function) a functor that will receive the return values

**Return values**
- The `services`: Array of objects.

The properties of the return object are:
- `name`
- `url`

See example: `rapp-api/js/examples/available_services.js`

## Cognitive Exercises
A series of classes which are used to play cognitive games.
Types of games are:

- ArithmeticCts
- AwarenessCts
- ReasoningCts

### cognitive-test-selector
Method `RAPPCloud.prototype.cognitive_test_chooser` in `rapp-api/js/includes/cloud/cognitive_test_chooser.js`
A call which will select a test.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Input arguments**
- `test_type`: (String) is the Cognitive Exercise test type. Can be one of ['ArithmeticCts', 'AwarenessCts', 'ReasoningCts', '']
- `test_subtype` (String) Use this to force select from this subtype. Defaults to empty string "".
- `test_diff`: (String) Use this to force select from this difficulty. Defaults to empty string "".
- `test_index`: (String) Use this to force select from this id. Defaults to empty string "".
- `callback`: (function) is the functor that will receive the return values

**Return values**
- array `questions`
- array `possib_ans`
- array `correct_ans`
- string `test_instance`
- string `test_type`
- string `test_subtype`

See example `rapp-api/js/examples/cognitive_game.js`

### cognitive-record-performance
Method `RAPPCloud.prototype.cognitive_record_performance` in `rapp-api/js/includes/cloud/cognitive_record_performance.js`
A call used to record performance for a user.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Input arguments**
- `test_instance`: (String) is the Cognitive Exercise test instance. The full cognitive test entry name as reported by the cognitive_test_chooser()
- `score`: (Integer) User's performance score on given test entry.
- `callback`: (function) the functor that will receive the return values

**Return values**
- `performance_entry`: (string). A performance entry

See example `rapp-api/js/examples/cognitive_game.js`

### cognitive-get-history
Method `RAPPCloud.prototype.cognitive_get_history` in `rapp-api/js/includes/cloud/cognitive_get_history.js`
A call used to obtain user's history.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Input arguments**
- `callback`: (function) the functor that will receive the return values
- `test_type`: (String) Cognitive Exercise test type. Can be one of ['ArithmeticCts', 'AwarenessCts', 'ReasoningCts'] or leave empty ("") for all. Default: "".
- `from_time`: (Integer) Unix timestamp. Default: 0.
- `to_time`: (Integer) Unix timestamp. Default: 0

**Return values**
- `records`: a JSON string with the history of user's records(not-parsed)

See example `rapp-api/js/examples/cognitive_game.js`

### cognitive-get-scores
Method `RAPPCloud.prototype.cognitive_get_scores` in `rapp-api/js/includes/cloud/cognitive_get_scores.js`
A call used to quqery scores.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Cognitive-Exercise)

**Input arguments**
- `callback`: (function) the functor that will receive the return values
- `up_to_time`: (Integer) Unix timestamp. Return scores that have been recorder up to this time value. Default: 0.
- `test_type`: (String) Cognitive Exercise test type. Can be one of ['ArithmeticCts', 'AwarenessCts', 'ReasoningCts'] or leave empty ("") for all. Default: "".

**Return values**
- `test_classes`: (array) An array with the test classes indexes
- `scores`: (array) Array with the respective scores for the tests

See example `rapp-api/js/examples/cognitive_game.js`

## Email
The platform supports sending and receiving email, when using your own
email account.

### email-fetch
Method `RAPPCloud.prototype.email_fetch` in `rapp-api/js/includes/cloud/email_fetch`
Request to fetch email from your account.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Email)

**Input arguments**
- `email`: (String) The user's email username
- `passwd`: (String) The user's email password
- `server`: (String) The email server's imap address, i.e. 'imap.gmail.com'
- `port`: (String) The email server imap port
- `email_status`: (String) Define which mails the users requests. Values: ALL, UNSEEN(DEFAULT)
- `from_date`: (Integer) Emails since date. Unix timestamp.
- `to_date`: (Integer) Emails until date. Unix timestamp.
- `num_emails`: (Integer): Number of requested emails
- `callback`: (function) The functor that will receive the return values

**Return values**
An array of email_entry objects, where an email_entry object has the following properties
- `sender`: (string) sender email address
- `receivers`: (array) the receivers' email addresses
- `body`: (string) body text (plaintext or html)
- `date`: (date) date
- `attachments`: (array) list of attachements
    
See example `rapp-api/js/examples/email_fetch.js`

### email-send
Method `RAPPCloud.prototype.email_send` in `rapp-api/js/includes/cloud/email_send`
Request an email to be sent.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Email)

**Input arguments**
- `email`: (String) The user's email username
- `passwd`: (String) The user's email password
- `server`: (String) The email server's smtp address, i.e. 'smtp.gmail.com'
- `port`: (String) The email server smtp port
- `recipients`: (Array) Email addresses of the recipients.
- `body` (String) The email body
- `subject`: (String) The email subject
- `file`: (String) Path to a file attachment. Single file. In case of multiple attachments a zip file must be send to this field name.

**Return values**
No return values

See example `rapp-api/js/examples/email_send.js`

## Geolocation
Method `RAPPCloud.prototype.geolocation` in `rapp-api/js/includes/cloud/geolocation.js`
Quering your location based on the IP of the robot.
Requires that you can establish what the external interface/address is.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Geolocator)

**Input arguments**
- `ipaddr`: (string) the robot's IP address
- `engine`: (string) the query engine to use. Defaults to 'ip-api' (Currently the only supported).
- `callback`: (function) the functor that will receive the return values (see below)

**Return values**
- `city`
- `country`
- `country_code`
- `latitude`
- `longtitude`
- ` zip`: the postcode
- `timezone`

See example `rapp-api/js/examples/geolocation.js`

## News
Method `RAPPCloud.prototype.news_explore` in `rapp-api/js/includes/cloud/news_explore.js`
For searching for news articles employing various news search engine APIs. 
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-News-Explorer)

**Input arguments**
- `news_engine`: (String) The news search engine to use.
- `keywords`: (Array) Desired keywords.
- `exclude_titles`: (Array) Reject list of previously read articles, in order to avoid duplicates.
- `region`: (String) Language/Region.
- `topic`: (String) Main topics, i.e. sports, politics, etc.
- `num_news`: (Integer) Number of news stories.
- `callback`: (function) the functor that will receive the result

**Return values**
- `news_stories`: Vector of stories. Each story is an object composed of `title`, `content`, `publisher`, `publishedDate` and `url`.

See example `rapp-api/js/examples/news_explore.js`
 
## Ontology
The Platform supports querying a KnowRob/RoboEarth instance.
Each type of query returns an XML URI, which you'll have to visit and parse
in order to obtain meaningful meta-data.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Knowrob-wrapper)

### ontology-subclasses-of
Method `RAPPCloud.prototype.ontology_subclasses_of` in `rapp-api/js/includes/cloud/ontology_subclasses_of.js`
Query the sub-classes of a class.

**Input arguments**
- `ontology_class`: (string) the entity being queried
- `callback`: (function) The callback functor will receive the return values.
- `recursive`: (boolean) set to true if you wish to search recursively

**Return values**
- `classes`: a list of subclasses

See example `rapp-api/js/examples/ontology_example.js`

### ontology-superclasses-of
Method `RAPPCloud.prototype.ontology_superclasses_of` in `rapp-api/js/includes/cloud/ontology_superclasses_of.js`
Query the super-classes of a class.

**Input arguments**
- `ontology_class`: (string) the entity being queried
- `callback`: (function) The callback functor will receive the return values.
- `recursive`: (boolean) set to true if you wish to search recursively

**Return values**
- `classes`: a list of superclasses

See example `rapp-api/js/examples/ontology_example.js`

### ontology-is-subsuperclass-of
Method `RAPPCloud.prototype.ontology_is_subsuperclass_of` in `rapp-api/js/includes/cloud/ontology_is_subsuperclass_of`
Query if a sub-class is the super-class of another entity.

**Input arguments**
- `parent_class`: (string) the super-class queried
- `child_class`: (string) the sub-class queried
- `recursive`: (boolean) set to true for a recursive search
- `callback`: (function) The callback functor will receive the return values.

**Return values**
- `result`: (boolean) true if the subclass is the super class of the query, false if not

See example `rapp-api/js/examples/ontology_example.js`

## Path Planning
The platform offers a path planning service.
The requirement is that you must upload a map, and index the name of the map.
You may then request a path using that map and certain parameters.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Path-planner)

### path-planning-2d
Method `RAPPCloud.prototype.path_planning_plan_path_2d` in `rapp-api/js/includes/cloud/path_planning_plan_path_2d.js`
Request a 2D plan from the platform.

**Input arguments**
- `map_name`: (string) the name of the map
- `robot_type`: (string) the type of your robot
- `algorithm`: the path planning algorithm to apply (e.g., *dijkstra*)
- `start`: (Object - ROS-GeometryMsgs/PoseStamped) the starting pose of the robot
- `goal`: (Object - ROS-GeometryMsgs/PoseStamped) the goal/target pose of the robot
- `callback`: The callback functor will receive the return values.

**Return values**
- `path`: (array or one of the following strings: '0', '2', '3', '4'). The discovered path if one is found in the form of an array of waypoints from start to goal, where the first one equals start and the last one equals goal. It can also be one of the aforementioned strings, when no plan is found meaning the following:
0: No plan found.
2: Wrong map name.
3: Wrong robot type
4: Wrong algorithm

See example: `rapp-api/js/examples/plan_path.js`

### path-upload-map
Method `RAPPCloud.prototype.path_planning_upload_map` in `rapp-api/js/includes/cloud/path_planning_upload_map.js`
This call will upload a 2D PNG map to the platform.
A list of maps and their descriptors can be found in the [platform](https://github.com/rapp-project/rapp-platform/tree/master/rapp_path_planning/rapp_map_server/maps).
The overall idea is to represent boundaries and obstacles with pixels, 
and set the appropriate YAML meta-data.

**Input arguments**
- `png_file`: the map image PNG file
- `yaml_file`: The map description YAML file
- `map_name`: a unique map name

**Return values** 
No return values

See example: `rapp-api/js/examples/plan_path.js`

# Speech Services
The Platform offers speech-to-text (S2T) services,
as well as a text-to-speech (TTS) service.
A requirement is that a noise profile must be set (using the corresponfing API call) in order
to enable better performance.

## speech-google
Method `RAPPCloud.prototype.speech_recognition_google` in `rapp-api/js/includes/cloud/speech_recognition_google.js`
Uses the free Google Speech Recognition [API](https://cloud.google.com/speech/).
Requires that you have obtained an audio file as a WAV or OGG.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Speech-Detection-using-Google-API)

**Input arguments**
- `audio`: (string) is the path to the actual sound file 
- `audio_source`: (string) type of audio (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)
- `language`: (string) language locale (e.g., en, gr, etc.)
- `callback`: (function) The function that will receive the return values (see below).

**Return values**
- `possible_vectors`: (array) the array with the possible recognized sentences in vectors of words

See example: `rapp-api/js/examples/speech_to_text_google.js`

## speech-cmu-sphinx4
Method `RAPPCloud.prototype.speech_recognition_sphinx4` in `rapp-api/js/includes/cloud/speech_recognition_sphinx4.js` 
Uses a CMU [Sphinx4](http://cmusphinx.sourceforge.net/wiki/sphinx4:webhome) Backend to
process and recognise speech as text. Requires that you have obtained an audio file as a WAV or OGG.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Speech-Detection-using-Sphinx4)

**Input arguments**
- `audio`: (string) is the path to the actual sound file
- `audio_source`: (string) type of audio (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)
- `language`: (string) language locale (e.g., en, gr, etc.)
- `grammar`: a [JSGF](http://cmusphinx.sourceforge.net/doc/sphinx4/edu/cmu/sphinx/jsgf/JSGFGrammar.html) grammar data-file with rule definitions
- `words`: (array) keywords (strings) to search for in the audio data
- `sentences`: (array) sentences to search for in the audio data
- `callback`: (function) The callback functor will receive the return values.

**Return values**
- `words`: (array) a vector of recognised words

See example: `rapp-api/js/examples/speech_to_text_sphinx4.js`

## set-noise
Method `RAPPCloud.prototype.set_noise_profile` in `rapp-api/js/includes/cloud/set_noise_profile.js`
Sets the noise profile for CMU Sphinx4 cloud service.
Requires that you have obtained an audio file as a WAV or OGG,
which contains only backround, environment or microphone noise.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Audio-Processing)

**Input arguments**
- `audio`: (string) is the path to the actual sound file
- `audio_source`: (string) type of audio (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)

*Note*: there is no callback functor or return value in this class.

See example: `rapp-api/js/examples/set_noise_example.js`

## text-to-speech
Method `RAPPCloud.prototype.text_to_speech` in `rapp-api/js/includes/cloud/text_to_speech.js`.
Uses the [Espeak and MBrola](http://espeak.sourceforge.net/mbrola.html) backend
to generate audio files (WAV) from a queried text.
More [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Text-to-speech-using-Espeak-&-Mbrola)

**Input arguments**
- `text`: (string) the string containing the text you want
- `language`: (string) the language used
- `callback`: (function) the functor will receive the audio file.

**Return values**
- `payload`: audio data.
- `encoding`: the encoding of the audio data.
- `basename`: audio file basename.

See example: `rapp-api/js/examples/text_to_speech_example.js`

# Vision Services
The platforms offers a variety of Computer Vision (CV) services,
which are organised in two categories: *detection* and *recognition*.

## vision-door-angle
Method `RAPPCloud.prototype.hazard_detection_door` in `rapp-api/js/includes/cloud/hazard_detection_door.js`
Find if a door is open, and to what degree.
More details [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Hazard-Detection)

**Input arguments**
- `image`: (string). The path of the input image
- `image_format`: (string). The format of the input image
- `callback`: (function). The functor that will receive the return values

**Return values**
`door_angle`: estimate degrees of open door angle [0..100]

See example: `rapp-api/js/examples/door_detect.js`

## vision-face-detect
Method `RAPPCloud.prototype.face_detection` in `/includes/cloud/face_detection.js`
Detect faces in an image.
More details [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Face-Detection).

**Input arguments**
- `image`: (string). The path of the input image
- `image_format`: (string). The format of the input image
- `callback`: (function). The functor that will receive the return values
- `fast`: string. Only valid values are 'true' and 'false'. When 'true' the fast face detection service is called, which should be used for tracking applications. 

**Return values**
- `faces`: An array of found [faces](#face)

See example: `rapp-api/js/examples/face_detect.js`

## vision-human-detect
Method `RAPPCloud.prototype.human_detection` in `/includes/cloud/human_detection.js`
Detect humans in an image.
More details [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Human-Detection).

**Input arguments**
- `image`: (string). The path of the input image
- `image_format`: (string). The format of the input image
- `callback`: (function). The functor that will receive the return values

**Return values**
- `humans`: An array of found [humans](#human)

See example: `rapp-api/js/examples/human_detect.js`

## vision-light-detect
Method `RAPPCloud.prototype.hazard_detection_light` in `rapp-api/js/includes/cloud/hazard_detection_light.js`
Detect light level (luminoscity)
More details [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Hazard-Detection)

**Input arguments**
- `image`: (string). The path of the input image
- `image_format`: (string). The format of the input image
- `callback`: (function). The functor that will receive the return values

**Return values**
`light_level`: estimated luminoscity level [0..100]

See example: `rapp-api/js/examples/light_detect.js`

## vision-qrcode-detect
Method `RAPPCloud.prototype.qr_detection` in `/includes/cloud/qr_detection.js`
Detect qr codes in an image.
More details [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-QR-Detection).

**Input arguments**
- `image`: (string). The path of the input image
- `image_format`: (string). The format of the input image
- `callback`: (function). The functor that will receive a vector of the detected qr code(s) coordinates

**Return values**
- `qr_codes`: An array of found [qr codes](#qr_codes)

See example: `rapp-api/js/examples/qr_detect.js`

## vision-object-recognition
Method `RAPPCloud.prototype.object_recognition_caffe` in `/includes/cloud/object_recognition_caffe.js`
Recognise Objects using Berkeley's [Caffee](http://caffe.berkeleyvision.org/) framework.
More details [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Caffe-Wrapper)

**Input arguments**
- `image`: (string) is the input image
- `image_format`: (string) is the image format
- `callback`: (function) is the functor that will receive the return values

**Return values**
- `object_class`: the topmost object classification class

See example: `rapp-api/js/examples/object_recognition.js`

##vision-object-detection-learn-object
Method `RAPPCloud.prototype.object_detection_learn_object` in `/includes/cloud/object_detection_learn_object.js`
Learn objects give by the user.

**Input arguments**
- `image`: (string) is the input image
- `image_format`: (string) is the image format
- `name`: (string) the name of the object
- `callback`: (function) is the functor that will receive the return values

**Return values**
- `result`: (int) the result of the learning. `0` is everything is ok, `-1` there are no models and `-2` there is no image to analyse.

See example: `rapp-api/js/examples/object_detection_my_own_models.js`

##vision-object-detection-clear-models
Method `RAPPCloud.prototype.object_detection_clear_models` in `/includes/cloud/object_detection_clear_models.js`
Clears operational memory for selected user.

**Input arguments**
- `callback`: (function) is the functor that will receive the return values

**Return values**
- `result`: (int) the result of the learning. `0` is everything is ok, `-1` there are no models and `-2` there is no image to analyse.

See example: `rapp-api/js/examples/object_detection_my_own_models.js`

##vision-object-detection-load-models
Method `RAPPCloud.prototype.object_detection_load_models` in `/includes/cloud/object_detection_load_models.js`
Load one or more models to operational memory. This operation should be done at least once before first recognition request.

**Input arguments**
- `names`: (vector) The object names that are going to be loaded 
- `callback`: (function) is the functor that will receive the return values

**Return values**
- `result`: (int) the result of the learning. `0` is everything is ok, `-1` there are no models and `-2` there is no image to analyse.

See example: `rapp-api/js/examples/object_detection_my_own_models.js`

##vision-object-detection-find-objects
Method `RAPPCloud.prototype.object_detection_find_objects` in `/includes/cloud/object_detection_find_objects.js`
When set of models is loaded to operational memory, user can provide query image to detect objects on. 
If any object of known type is recognized, its center point in query image, model name and recognition score (certainty) is returned.

**Input arguments**
- `image`: (string) is the input image
- `image_format`: (string) is the image format
- `limit`: (string) the limit search to N best matches
- `callback`: (function) is the functor that will receive the return values

**Return values**
- `names`: (string) List of the found objects' names
- `centers`: (array) List of centroids in the image of the objects found
- `scores`: (array) List of scores of the found objects
- `result`: (int) the result of the learning. `0` is everything is ok, `-1` there are no models and `-2` there is no image to analyse.

See example: `rapp-api/js/examples/object_detection_my_own_models.js`

# Weather
The platform enables 3rd party weather reports and forecasting.

## weather-report-current
Method `RAPPCloud.prototype.weather_report_current` in `rapp-api/js/includes/cloud/weather_report_current.js`
Queries the current weather given certain arguments.
More details [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Weather-Reporter)

**Input arguments**
- `city`: (string) The desired city
- `weather_reporter`: (string) weather engine. Optional: defaults to Yahoo (yweather) if empty
- `metric`: (integer) set to 1 for true, 0 for false
- `callback`: (function) the functor that will receive the return values

**Return values**
- `weather`: an object of report data.

The properties of the return object are:
- `date`
- `temperature`
- `weather_description`
- `humidity`
- `visibility`
- `pressure`
- `wind_speed`
- `wind_temperature`
- `wind_direction`

See example `rapp-api/js/examples/weather_report_current.js`

## weather-report-forecast
Method `RAPPCloud.prototype.weather_report_current` in `rapp-api/js/includes/cloud/weather_report_forecast.js`
Queries the weather engine for a forecast.
More details [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Weather-Reporter)

**Input arguments**
- `city`: (string) The desired city
- `weather_reporter`: (string) weather engine. Optional: defaults to Yahoo (yweather) if empty
- `metric`: (integer) set to 1 for true, 0 for false
- `callback`: (function) the functor that will receive the return values

**Return values**
- `weather`: a vector with the objects of report data.

The properties of the return objects are:
- `high_temp`
- `low_temp`
- `description`
- `date`

See example `rapp-api/js/examples/weather_report_forecast.js`

-------------------

##face
Method `RAPPObject.prototype.Face` in `rapp-api/js/includes/objects/face.js`
Method which describes a face with cartesian coordinates.

**Constructor arguments**
- `Face(top_left_x, top_left_y, bottom_right_x, bottom_right_y)`: Construct using face coordinates. The coordinates will be x and y from the top left and bottom right points of the rectangle formed by the face.

**Prototype methods of the Object**
- `Face.prototype.is_equal`: Equality operator.
    Arguments:
    - `face2`: The face object to compare with
    Returns: True or False.
- `Face.prototype.get_up_left_x`: Return the top left x coordinate
- `Face.prototype.get_up_left_y`: Return the top left y coordinate
- `Face.prototype.get_down_right_x`: Return the bottom right x coordinate
- `Face.prototype.get_down_right_y`: Return the bottom left y coordinate

##human
Method `RAPPObject.prototype.Human` in `rapp-api/js/includes/objects/human.js`
To describe the human coordinates.

**Constructor arguments**
- `Human(top_left_x, top_left_y, bottom_right_x, bottom_right_y)`: Construct using human coordinates. The coordinates will be x and y from the top left and bottom right points of the rectangle formed by the human.

**Methods of the class**
- `Human.prototype.is_equal`: Equality operator.
    Arguments:
    - `human2`: The human object to compare with
    Returns: True or False.
- `Human.prototype.get_up_left_x`: Return the top left x coordinate
- `Human.prototype.get_up_left_y`: Return the top left y coordinate
- `Human.prototype.get_down_right_x`: Return the bottom right x coordinate
- `Human.prototype.get_down_right_y`: Return the bottom left y coordinate


