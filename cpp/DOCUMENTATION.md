# C++ DOCUMENTATION
-----------------------

- C++ API cloud classes
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
  - [Weather](#weather)

## Available Services
A call which will return a list of pairs of strings, the first string naming the service name and the second defining the URL.

**Input arguments**
- `std::function<void(std::vector<service>)> callback` : a callback functor receiving the list of services

**Return values**
- The `service` type is defined as `typedef std::pair<std::string, std::string> service`

See example: `rapp-api/cpp/examples/available_services.cpp`

## Cognitive Exercises
A series of classes which are used to play cognitive games.
Types of games are:

- ArithmeticCts
- AwarenessCts
- ReasoningCts

### cognitive-test-selector

A call which will select a test.
**Input arguments**
- `const std::string test_type`: sets the type of test
- `const std::string test_subtype`: sets the test sub-type
- `const std::string test_diff`: sets the difficulty value
- `const std::string test_index`: sets the exercise index
- `functor callback`: receives a `functor` type (see below)

The `functor` is type-defined as:

```
typedef std::function<void(std::vector<std::string>,
                           std::vector<std::vector<std::string>>,
                           std::vector<std::string>,
                           std::string,
                           std::string,
                           std::string)> functor;
```

The items in the functor represent the return values.

**Return values**
- array questions
- possible answers
- correct answers
- test instance names
- exercise type
- exercise sub type
- error message

See example `rapp-api/cpp/examples/cognitive_games.cpp`

### cognitive-record-performance
A call used to record performance for a user.

**Input arguments**
- `const std::string test_instance`: specifies the test
- `const float score`: sets the score
- `std::function<void(std::string)> callback` will receive the platform's response

**Return values**
- `std::string`: a performance entry

See example `rapp-api/cpp/examples/cognitive_games.cpp`

### cognitive-get-history
A call used to obtain user's history.

**Input arguments**
- `unsigned int from_time`: starting from time
- `unsigned int to_time`:  ending time
- `const std::string test_type`: test type
- `std::function<void(std::string)> callback`: functor receiving return values

**Return values**
- `std::string`: a JSON record of user's history (not-parsed)

See example `rapp-api/cpp/examples/cognitive_games.cpp`

### cognitive-get-scores
A call used to quqery scores.

**Input arguments**
- `unsigned int up_to_time`: query scores up to a specific time
- `const std::string test_type`: the type of test
- `std::function<void(std::vector<std::string>, std::vector<float>)> callback`: functor will receive return values

**Return values**
- `std::vector<std::string>`: name of test type
- `std::vector<float>`: respective score for test

See example `rapp-api/cpp/examples/cognitive_games.cpp`

## Email
The platform supports sending and receiving email, when using your own
email account.

### email-fetch
Request to fetch email from your account.

**Input arguments**
- `const std::string email`: email account username
- `const std::string pwd`: plaintext password
- `const std::string server`: IMAP server address
- `const std::string port`: IMAP Port
- `const std::string email_status`: email status (ALL, UNSEEN)
- `const unsigned int from_date`: fetch from date (UNIX timestamp)
- `const unsigned int to_date`: fetch to date (UNIX timestamp)
- `const unsigned int num_emails`: limit number of emails

The callback functor receives the return values.

**Return values**
- `std::string`: sender address
- `std::vector<std::string>`: receivers
- `std::string`: body text (plaintext or html)
- `std::string`: date
- `std::vector<std::string>`: list of attachements

See example `rapp-api/cpp/examples/email_handling.cpp`

### email-send
Request an email to be sent.

**Input arguments**
- `const std::string email`: user's email address/username
- `const std::string pwd`: user's password
- `const std::string server`: SMTP server 
- `const std::string port`: SMTP port
- `const std::vector<std::string> recipients`: list of email addresses
- `const std::string body`: actual email body (plaintext or html)
- `const std::string subject`: email subject
- `const std::vector<rapp::types::byte> data`: a vector of attachments, of raw binary data

The callback functor may receive a JSON of errros.

**Return values**
- `std::string`: a JSON of errors (will default to empty if no errrors)

## Geolocation
Quering your location based on the IP of the robot.
Requires that you can establish what the external interface/address is.

**Input arguments**
- `const std::string ipaddr`: the robot's IP address
- `const std::string engine`: the query engine (use `ip-api`)

Callback functor receives return values.

**Return values**
- `std::string`: City
- `std::string`: Country
- `std::string`: Country code
- `float`: latitude
- `float`: longtitude
- `std::string`: zip/postcode
- `std::string`: timezone

See example `rapp-api/cpp/examples/geolocation.cpp`

## Ontology
The Platform supports querying a KnowRob/RoboEarth instance.
Eeach type of query returns an XML URI, which you'll have to visit and parse
in order to obtain meaningful meta-data.

### ontology-subclasses-of
Query the sub-classes of a class.

**Input arguments**
- `std::string ontology_class`: the entity being queried
- `bool recursive`: set to true if you wish to search recursively

The callback functor will receive the return values.

**Return values**
- `std::vector<std::string>`: a list of subclasses

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

### ontology-superclasses-of
Query the super-classes of a class.

**Input arguments**
- `const std::string ontology_class`: the entity being queried
- `bool recursive`: set to true if you wish to search recursively

The callback functor will receive the return values.

**Return values**
- `std::vector<std::string>`: a list of subclasses

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

### ontology-is-subsuperclass-of
Query if a sub-class is the super-class of another entity.

**Input arguments**
- `const std::string parent_class`: the super-class queried
- `const std::string child_class`: the sub-class queried
- `bool recursive`: set to true for a recursive search

The callback functor will receive the return values.

**Return values**
- `std::vector<bool>`: true if the subclass is the super class of the query, false if not

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

## Path Planning
The platform offers a path planning service.
The requirement is that you must upload a map, and index the name of the map.
You may then request a path using that map and certain parameters.

### path-planning-2d
Request a 2D plan from the platform.
*Note*: see classes:
- `rapp::object::planned_path` which is the return class type
- `rapp::object::pose_stamped` which is the argument class type used

**Input arguments**
- `const std::string map_name`: the name of the map
- `const std::string robot_type`: the type of your robot
- `const std::string algorithm`: the algorithm used (e.g., *dijkstra*)
- `const rapp::object::pose_stamped start`: the starting pose of the robot
- `const rapp::object::pose_stamped goal`: the goal/target pose of the robot

As always, the callback functor will receive the return values.

**Return values**
- `rapp::object::planned_path`: the discovered path

See example: `rapp-api/cpp/examples/path_planning.cpp`

### path-upload-map
This call will upload a 2D PNG map to the platform.
A list of maps and their descriptors can be found in the [platform](https://github.com/rapp-project/rapp-platform/tree/master/rapp_path_planning/rapp_map_server/maps).
The overall idea is to represent boundaries and obstacles with pixels, 
and set the appropriate YAML meta-data.

**Input arguments**
- `const rapp::object::picture & png_file`: the map PNG file
- `const rapp::object::yaml & yaml_file`: a YAML file
- `const std::string map_name`: a unique map name

As always, the callback functor will receive the return values.

**Return values** Optional
- `std::string`: a JSON string with an error if one occurs

See example: `rapp-api/cpp/examples/path_planning.cpp`

# Speech Services
The Platform offers speech-to-text (S2T) services,
as well as a text-to-speech (TTS) service.
A requirement is that a noise profile must be set in order
to enable better performance.

## speech-google
Uses the free Google Speech Recognition [API](https://cloud.google.com/speech/).
Requires that you have obtained an audio file as a WAV or OGG.

**Input arguments**
- `const std::vector<rapp::types::byte> audio_bytearray`: a vector of bytes which make up an audio file
- `const rapp::types::audio_source audio_src`: type of audio (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)
- `const std::string language`: language locale (e.g., en, gr, etc.)

The callback functor will receive the return values.
**Return values**
- `std::vector<std::string>`: words recognised
- `std::vector<std::vector<std::string>>`: alternative sentences recognised

See example: `rapp-api/cpp/examples/speech_recognition_google.cpp`

## speech-cmu-sphinx4
Uses a CMU [Sphinx4](http://cmusphinx.sourceforge.net/wiki/sphinx4:webhome) Backend to
process and recognise speech as text. Requires that you have obtained an audio file as a WAV or OGG.

**Input arguments**
- `const std::vector<rapp::types::byte> audio_data`: audio data bytes, taken from a `rapp::object::audio`
- `const rapp::types::audio_source audio_src`: type of audio (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)
- `const std::string language`: language locale (e.g., en, gr, etc.)
- `const std::vector<std::string> grammar`: a [JSGF](http://cmusphinx.sourceforge.net/doc/sphinx4/edu/cmu/sphinx/jsgf/JSGFGrammar.html) grammar data-file with rule definitions
- `const std::vector<std::string> words`: keywords to search for in the audio data
- `const std::vector<std::string> sentences`: sentences to search for in the audio data

As always, the callback functor will receive the return values.

**Return values**
- `std::vector<std::string> words`: a list of rezognised words

See example: `rapp-api/cpp/examples/speech_recognition_sphinx4.cpp`

## set-noise
Sets the noise profile for CMU Sphinx4 cloud service.
Requires that you have obtained an audio file as a WAV or OGG,
which contains only backround, environment or microphone noise.

**Input arguments**
- `const std::vector<rapp::types::byte> audio_bytearray`: the audio data file (WAV, OGG) with the noise
- `const rapp::types::audio_source audio_src`: the audio type (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)

*Note*: there is no callback functor or return value in this class.

## text-to-speech
Uses the [Espeak and MBrola](http://espeak.sourceforge.net/mbrola.html) backend
to generate audio files (WAV) from a queried text.

**Input arguments**
- `const std::string text`: the string containing the text you want
- `const std::string language`: the language used

Callback functor will receive the audio file.

**Return values**
- `rapp::object::audio`: an audio file with the speech requested.

See example: `rapp-api/cpp/examples/set_noise_profile.cpp`

# Vision Services
The platforms offers a variety of Computer Vision (CV) services,
which are organised in two categories: *detection* and *recognition*.

## vision-door-angle
Find if a door is open, and to what degree.

**Input arguments**
- `const rapp::object::picture & image`: an imagine used to detect an open door

As always, the callback functor will receive the return values.

**Return values**
- `double door_angle`: degrees of open door angle

See example: `rapp-api/cpp/examples/hazard_detect.cpp`

## vision-face-detect
Detect faces in an image.

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for detection
- `bool fast`: set true to run faster but less accurately

As always, the callback functor will receive the return values.

**Return values**
- `std::vector<rapp::object::face>`: a list of detected faces

See example: `rapp-api/cpp/examples/face_detect.cpp`

## vision-human-detect
Detect humans in an image.

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for detection

As always, the callback functor will receive the return values.

**Return values**
- `std::vector<rapp::object::human>`: list of humans detected

See example: `rapp-api/cpp/examples/human_detect.cpp`

## vision-light-detect
Detect light level (luminoscity)

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for detection

As always, the callback functor will receive the return values.

**Return values**
- `int light_level`: luminoscity level

See example: `rapp-api/cpp/examples/light_detection.cpp`

## vision-qrcode-detect
Detect and scan QR code.

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for detection

As always, the callback functor will receive the return values.

**Return values**
- `std::vector<rapp::object::qr_code>`: list of qr objects detected

See example: `rapp-api/cpp/examples/qr_detect.cpp`

## vision-object-recognition
Recognise Objects using [Caffee](http://caffe.berkeleyvision.org/).

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for object recognition

As always, the callback functor will receive the return values.

**Return values**
- `std::string`: the topmost object classification class

See example: `rapp-api/cpp/examples/object_recognition.cpp`

