# C++ DOCUMENTATION
-----------------------

- C++ API cloud classes
  - [Authentication](#authentication)
    - [Login User](#login-user)
    - [Register User from Platform](#register-user-from-platform)
    - [Register User from Store](#register-user-from-store)
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
    - [Current Report](#weather-report-current)
- C++ API object classes
  - [Audio](#audio)
  - [Face](#face)
  - [Globals](#globals)
  - [Human](#human)
  - [Msg Metadata](#msg-metadata)
  - [Picture](#picture)
  - [Planned Path](#planned-path)
  - [Point](#point)
  - [Pose](#pose)
  - [Pose stamped](#pose-stamped)
  - [Qr Code](#qr-code)
  - [Quaternion](#quaternion)
  - [Time](#time)

##Authentication
A serie of classes which are used to register and login in RAPP-Platform or RAPP-Store.
All classes of authentication in `rapp/cloud/authentication.hpp`

### login-user
Class `rapp::cloud::login_user`
An existing user login in the Platform or Store.

**Input arguments**
- `std::string username`: Account username
- `std::string password`: Account password
- `std::string device_token`: The device from which a user tries to login
- `std::function<void(std::string)> callback`: a callback functor which receive the return values

**Return values**
- `std::string token`: Token used for accessing RAPP-Platform resources.

### register-user-from-platform
Class `rapp::cloud::register_user_from_platform`
Add new platform user using RAPP-Platform credentials.

**Input arguments**
- `std::string creator_username`: Robot admin account username of RAPP-Platform
- `std::string creator_password`: Robot admin account password of RAPP-Platform
- `std::string new_user_username`: New user's account username
- `std::string new_user_password`: New user's account password
- `std::string language`: The language choosen by the user
- `std::function<void(std::string)> callback`: a callback functor which receive the return values

**Return arguments**
- `std::string suggested_username`: Suggested username if the provided one already exists.

### register-user-from-store
Class `rapp::cloud::register_user_from_store`
Add new platform user using RAPP-Platform credentials.

**Input arguments**
- `std::string username`: New user's account username.
- `std::string password`: New user's account password.
- `std::string device_token`: Creator device token from RAPP Store. 
- `std::string language`: The language choosen by the user.
- `std::function<void(std::string)> callback`: a callback functor which receive the return values.

**Return arguments**
- `std::string suggested_username`: Suggested username if the provided one already exists.

## Available Services
Class `rapp::cloud::available_services` in `rapp/cloud/available_services.hpp`.
A cloud call which will return a list of pairs of strings, the first string naming the service name and the second defining the URL.

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

All classes of cognitive exercises are in `rapp/cloud/cognitive_exercises.hpp`

### cognitive-test-selector
Class `rapp::cloud::cognitive_test_selector`
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
Class `rapp::cloud::cognitive_record_performance`
A call used to record performance for a user.

**Input arguments**
- `const std::string test_instance`: specifies the test
- `const float score`: sets the score
- `std::function<void(std::string)> callback` will receive the platform's response

**Return values**
- `std::string`: a performance entry

See example `rapp-api/cpp/examples/cognitive_games.cpp`

### cognitive-get-history
Class `rapp::cloud::cognitive_get_history`
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
Class `rapp::cloud::cognitive_get_scores`
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
All email-related classes are in `rapp/cloud/email.hpp`

### email-fetch
Class `rapp::cloud::email_fetch`
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
- `function callback`: receives the return value (see below)

The `function callback` complete: 

```
std::function<void(std::vector<std::tuple<std::string, 
                                          std::vector<std::string>,
                                          std::string,
                                          std::string,
                                          std::vector<std::string>>>)> callback
```


**Return values**
- `std::string`: sender address
- `std::vector<std::string>`: receivers
- `std::string`: body text (plaintext or html)
- `std::string`: date
- `std::vector<std::string>`: list of attachements

See example `rapp-api/cpp/examples/email_handling.cpp`

### email-send
Class `rapp::cloud::email_send`
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
- `std::function<void(std::string)> callback`: The callback functor may receive a JSON of errors.

**Return values**
- `std::string`: a JSON of errors (will default to empty if no errrors)

## Geolocation
Quering your location based on the IP of the robot.
Requires that you can establish what the external interface/address is.
Header is in `rapp/cloud/geolocation.hpp`
Class `rapp::cloud::geolocation`

**Input arguments**
- `const std::string ipaddr`: the robot's IP address
- `const std::string engine`: the query engine (use `ip-api`)
- `function callback`: receives the return value (see below)

The `function callback` complete: 

```
std::function<void(std::string,
                   std::string,
                   std::string,
                   float,
                   float,
                   std::string,
                   std::string,
                   std::string)> callback
```

**Return values**
- `std::string`: City
- `std::string`: Country
- `std::string`: Country code
- `float`: latitude
- `float`: longtitude
- `std::string`: zip/postcode
- `std::string`: timezone

See example `rapp-api/cpp/examples/geolocation.cpp`

## News
For searching for news articles employing various news search engine APIs. 
Header is in `rapp/cloud/news.hpp`
Class `rapp::cloud::news_explore`

**Input arguments**
- `const std::string news_engine`: The news search engine to use. If not set, default value is `eventregistry`
- `const std::vector<std::string> keywords`: The list with desired words.
- `const std::vector<std::string> exclude_titles`: Reject list of previously read articles to avoid duplicates. If not set, default value is `[]`.
- `const std::string region`: To specify a region. Optional.
- `const std::string topic`: Main topic of the news. Optional.
- `const unsigned int num_news`: Number of news stories. If it is not set, default value is `1`.
- `std::function<void(std::vector<std::vector<std::string>>)> callback`: Callback functor receives return values.

**Return values**
- `std::vector<std::vector<std::string>>`: Vector of stories. Each story is composed of `title`, `content`, `publisher`, `publishedDate` and `url`.

See example `rapp-api/cpp/examples/news.cpp`
 
## Ontology
The Platform supports querying a KnowRob/RoboEarth instance.
Eeach type of query returns an XML URI, which you'll have to visit and parse
in order to obtain meaningful meta-data.
All classes are in `rapp/cloud/ontology.hpp`

### ontology-subclasses-of
Class `rapp::cloud::ontology_subclasses_of`
Query the sub-classes of a class.

**Input arguments**
- `std::string ontology_class`: the entity being queried
- `bool recursive`: set to true if you wish to search recursively
- `std::function<void(std::vector<std::string>)> callback`:The callback functor will receive the return values.

**Return values**
- `std::vector<std::string>`: a list of subclasses

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

### ontology-superclasses-of
Class `rapp::cloud::ontology_superclasses_of`
Query the super-classes of a class.

**Input arguments**
- `const std::string ontology_class`: the entity being queried
- `bool recursive`: set to true if you wish to search recursively
- `std::function<void(std::vector<std::string>)> callback`:The callback functor will receive the return values.

**Return values**
- `std::vector<std::string>`: a list of subclasses

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

### ontology-is-subsuperclass-of
Class `rapp::cloud::ontology_is_subsuperclass_of`
Query if a sub-class is the super-class of another entity.

**Input arguments**
- `const std::string parent_class`: the super-class queried
- `const std::string child_class`: the sub-class queried
- `bool recursive`: set to true for a recursive search
- `std::function<void(bool result)> callback`: The callback functor will receive the return values.

**Return values**
- `std::vector<bool>`: true if the subclass is the super class of the query, false if not

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

## Path Planning
The platform offers a path planning service.
The requirement is that you must upload a map, and index the name of the map.
You may then request a path using that map and certain parameters.
All classes are in `rapp/cloud/path_planning.hpp`

### path-planning-2d
Class `rapp::cloud::plan_path_2d`
Request a 2D plan from the platform.
*Note* see classes:
- `rapp::object::planned_path` which is the return class type
- `rapp::object::pose_stamped` which is the argument class type used

**Input arguments**
- `const std::string map_name`: the name of the map
- `const std::string robot_type`: the type of your robot
- `const std::string algorithm`: the algorithm used (e.g., *dijkstra*)
- `const rapp::object::pose_stamped start`: the starting pose of the robot
- `const rapp::object::pose_stamped goal`: the goal/target pose of the robot
- `std::function<void(rapp::object::planned_path)> callback`: The callback functor will receive the return values.

**Return values**
- `rapp::object::planned_path`: the discovered path

See example: `rapp-api/cpp/examples/path_planning.cpp`

### path-upload-map
Class `rapp::cloud::path_upload_map`
This call will upload a 2D PNG map to the platform.
A list of maps and their descriptors can be found in the [platform](https://github.com/rapp-project/rapp-platform/tree/master/rapp_path_planning/rapp_map_server/maps).
The overall idea is to represent boundaries and obstacles with pixels, 
and set the appropriate YAML meta-data.

**Input arguments**
- `const rapp::object::picture & png_file`: the map PNG file
- `const rapp::object::yaml & yaml_file`: a YAML file
- `const std::string map_name`: a unique map name
- `std::function<void(std::string)> callback`: The callback functor will receive the return values.

**Return values** Optional
- `std::string`: a JSON string with an error if one occurs

See example: `rapp-api/cpp/examples/path_planning.cpp`

# Speech Services
The Platform offers speech-to-text (S2T) services,
as well as a text-to-speech (TTS) service.
A requirement is that a noise profile must be set in order
to enable better performance.

## speech-google
Class `rapp::cloud::speech_recognition_google`
Uses the free Google Speech Recognition [API](https://cloud.google.com/speech/).
Requires that you have obtained an audio file as a WAV or OGG.

**Input arguments**
- `const std::vector<rapp::types::byte> audio_bytearray`: a vector of bytes which make up an audio file
- `const rapp::types::audio_source audio_src`: type of audio (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)
- `const std::string language`: language locale (e.g., en, gr, etc.)
- `function callback`: it will receive the return values (see below).

The function callback complete:

```
std::function<void(std::vector<std::string>, std::vector<std::vector<std::string>>)> callback
```

**Return values**
- `std::vector<std::string>`: words recognised
- `std::vector<std::vector<std::string>>`: alternative sentences recognised

See example: `rapp-api/cpp/examples/speech_recognition_google.cpp`

## speech-cmu-sphinx4
Class `rapp::cloud::speech_recognition_sphinx4`
Uses a CMU [Sphinx4](http://cmusphinx.sourceforge.net/wiki/sphinx4:webhome) Backend to
process and recognise speech as text. Requires that you have obtained an audio file as a WAV or OGG.

**Input arguments**
- `const std::vector<rapp::types::byte> audio_data`: audio data bytes, taken from a `rapp::object::audio`
- `const rapp::types::audio_source audio_src`: type of audio (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)
- `const std::string language`: language locale (e.g., en, gr, etc.)
- `const std::vector<std::string> grammar`: a [JSGF](http://cmusphinx.sourceforge.net/doc/sphinx4/edu/cmu/sphinx/jsgf/JSGFGrammar.html) grammar data-file with rule definitions
- `const std::vector<std::string> words`: keywords to search for in the audio data
- `const std::vector<std::string> sentences`: sentences to search for in the audio data
- `std::function<void(std::vector<std::string> words)> callback`: The callback functor will receive the return values.

**Return values**
- `std::vector<std::string> words`: a list of recognised words

See example: `rapp-api/cpp/examples/speech_recognition_sphinx4.cpp`

## set-noise
Class `rapp::cloud::set_noise_profile`
Sets the noise profile for CMU Sphinx4 cloud service.
Requires that you have obtained an audio file as a WAV or OGG,
which contains only backround, environment or microphone noise.

**Input arguments**
- `const std::vector<rapp::types::byte> audio_bytearray`: the audio data file (WAV, OGG) with the noise
- `const rapp::types::audio_source audio_src`: the audio type (nao_ogg, nao_wav_1_ch, nao_wav_4_ch, headset)

*Note*: there is no callback functor or return value in this class.

## text-to-speech
Class `rapp::cloud::text_to_speech` in `rapp/cloud/text_to_speech.hpp`.
Uses the [Espeak and MBrola](http://espeak.sourceforge.net/mbrola.html) backend
to generate audio files (WAV) from a queried text.

**Input arguments**
- `const std::string text`: the string containing the text you want
- `const std::string language`: the language used
- `std::function<void(audio_file)> callback`: Callback functor will receive the audio file.

**Return values**
- `rapp::object::audio`: an audio file with the speech requested.

See example: `rapp-api/cpp/examples/set_noise_profile.cpp`

# Vision Services
The platforms offers a variety of Computer Vision (CV) services,
which are organised in two categories: *detection* and *recognition*.
Each respective category is in `rapp/cloud/vision_detection.hpp` and `rapp/cloud/vision_recognition.hpp`.

## vision-door-angle
Class `rapp::cloud::door_angle_detection`
Find if a door is open, and to what degree.

**Input arguments**
- `const rapp::object::picture & image`: an imagine used to detect an open door
- `std::function<void(double door_angle)> callback`: The callback functor will receive the return values.

**Return values**
- `double door_angle`: degrees of open door angle

See example: `rapp-api/cpp/examples/hazard_detect.cpp`

## vision-face-detect
Class `rapp::cloud::face_detection`
Detect faces in an image.

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for detection
- `bool fast`: set true to run faster but less accurately
- `std::function<void(std::vector<rapp::object::face>)> callback`: The callback functor will receive the return values.

**Return values**
- `std::vector<rapp::object::face>`: a list of detected faces

See example: `rapp-api/cpp/examples/face_detect.cpp`

## vision-human-detect
Class `rapp::cloud::human_detection`
Detect humans in an image.

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for detection
- `std::function<void(std::vector<rapp::object::human>)> callback`: The callback functor will receive the return values.

**Return values**
- `std::vector<rapp::object::human>`: list of humans detected

See example: `rapp-api/cpp/examples/human_detect.cpp`

## vision-light-detect
Class `rapp::cloud::light_detection`
Detect light level (luminoscity)

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for detection
- `std::function<void(int light_level)> callback`: The callback functor will receive the return values.

**Return values**
- `int light_level`: luminoscity level

See example: `rapp-api/cpp/examples/light_detection.cpp`

## vision-qrcode-detect
Class `rapp::cloud::qr_detection`
Detect and scan QR code.

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for detection
- `std::function<void(std::vector<rapp::object::qr_code>)> callback`: the callback functor will receive the return values.

**Return values**
- `std::vector<rapp::object::qr_code>`: list of qr objects detected

See example: `rapp-api/cpp/examples/qr_detect.cpp`

## vision-object-recognition
Class `rapp::cloud::object_recognition`
Recognise Objects using Berkley's [Caffee](http://caffe.berkeleyvision.org/) framework.

**Input arguments**
- `const rapp::object::picture & image`: the image data being used for object recognition
- `std::function<void(std::string)> callback`: The callback functor will receive the return values.

**Return values**
- `std::string`: the topmost object classification class

See example: `rapp-api/cpp/examples/object_recognition.cpp`

# Weather
The platform enables 3rd party weather reports and forecasting.
The classes are in `rapp/cloud/weather_report.hpp`

## weather-report-current
Class `rapp::cloud::weather_report_current`
Queries the current weather given certain arguments.

**Input arguments**
- `const std::string city`: current city location
- `const std::string weather_reporter`: weather engine (Optional: defaults to Yahoo if empty)
- `const unsigned int metric`: set to 1 for true, 0 for false
- `functor callback`: receives a `functor` type (see below)

The `functor` is type-defined as:

```
 typedef std::function<void(std::vector<std::string>)> functor;
```

**Return values**
- `std::vector<std::string>`: a list of report data.

The `std::string` entries in the return vector are:
- Date
- Temperature
- Description
- Humidity
- Visibility
- Pressure
- Wind speed
- Wind Temperature
- Wind Direction

See example `rapp-api/cpp/examples/weather.cpp`

## weather-report-forecast
Class `rapp::cloud::weather_report_forecast`
Queries the weather engine for a forecast.

**Input arguments**
- `const std::string city`: current city
- `const std::string weather_reporter`: weather engine (Optional: defaults to Yahoo if empty)
- `const unsigned int metric`: set to 1 for true, 0 for false
- `forecast_functor callback`: receives a `functor` type (see below)

The `forecast_functor` is type-defined as:

```
typedef std::function<void(std::vector<std::vector<std::string>>)> forecast_functor;
```

**Return values**
- `std::vector<std::vector<std::string>>`: a list of report data.

The `std::string` entries in the return vector are:
- High Temperature
- Low Temperature
- Description
- Date

See example `rapp-api/cpp/examples/weather.cpp`

-------------------

##Audio
Class `rapp::object::audio` in `rapp-api/cpp/rapp/objects/audio.hpp`.
Class which wraps around raw bytes of an audiofile.

**Constructor arguments**
-`audio(const std::string filepath)`: Path of an audio file. 
-`audio(std::ifstream & bytestream)`: File stream of an audio.
-`audio(std::vector<rapp::types::byte> bytearray)`: Raw data bytes of the audio file.
-`audio(const audio &) = default`: Copy constructor

**Methods of the class**
- `std::vector<rapp::types::byte> bytearray() const`: Get audio as array of bytes
- `bool operator==(const audio & rhs) const`: Compare if the audios are equal.
- `bool operator!=(const audio & rhs) const`: Compare if audios are not the same.
- `audio & operator=(const audio &) = default`: Assignment operator.
- `bool save(const std::string filepath)`: Save audio to filepath.

##Face
Class `rapp::object::face` in `rapp-api/cpp/rapp/objects/face.hpp`
Class which describes a face cartesian coordinate.

**Constructor arguments**
- `face(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y)`: Construct using face coordinates. The coordinates will be x and y from the top left and bottom right points of the rectangle formed by the face.
- `face() = default`: Empty constructor
- `face(const face &) = default`: Copy constructor
- `face(const json::const_iterator & face_it)`: Constructor using the information from JSON

**Methods of the class**
- `json::object_t to_json() const`: Return a JSON object
- `bool operator==(const face & rhs) const`: Equality operator
- `float get_left_x() const`: Return the top left x coordinate
- `float get_left_y() const`: Return the top left y coordinate
- `float get_right_x() const`: Return the bottom right x coordinate
- `float get_right_y() const`: Return the bottom left y coordinate

##Globals
Class `rapp::types` in `rapp/cpp/rapp/objects/globals.hpp`
Class to add global common types.

**Types**
- `byte`: To clarify memory variables
- `audio_source`: To select between the differents audio types (wav, ogg, etc.)

##Human
Class `rapp::object::human` in `rapp-api/cpp/rapp/objects/human.hpp`
To describe the human coordinates.

**Constructor arguments**
- `human(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y)`: Construct using human coordinates. The coordinates will be x and y from the top left and bottom right points of the rectangle formed by the human.
- `human() = default`: Empty constructor
- `human(const human &) = default`: Copy constructor
- `human(const json::const_iterator & human_it)`: Constructor using JSON

**Methods of the class**
- `json::object_t to_json() const`: Return a JSON object
- `bool operator==(const human & rhs) const`: Equality operator
- `float get_left_x() const`: Return top left x coordinate
- `float get_left_y() const`: Return top left y coordinate
- `float get_right_x() const`: Return bottom right x coordinate
- `float get_right_y() const`: Return bottom right y coordinate

##Msg_metadata
Class `rapp::object::msg_metadata` in `rapp-api/cpp/rapp/objects/msg_metadata.hpp`
Encapsulates metadata of another class (e.g. pose)

**Constructor arguments**
- `msg_metadata(int seq, rapp::object::time stamp, std::string frameid)`: Construct using data sequence `seq`, message data generation time stamp `stamp` and data coordination fram `frameid`.
- `msg_metadata() = default`: Empty constructor
- `msg_metadata(const rapp::object::msg_metadata &) = default`: Copy constructor
- `msg_metadata(const json::const_iterator & metadata)`: Constructor using JSON

**Methods of the class**
- `json::object_t to_json() const`: Return a JSON object
- `rapp::object::time get_time() const`: Return the parameter `stamp`
- `int get_seq() const`: Return the parameter `seq`
- `std::string get_frame() const`: Return the parameter `frameid`
- `bool operator==(const rapp::object::msg_metadata & rhs) const`: Equality operator

##Picture
Class `rapp::object::picture` in `rapp-api/cpp/rapp/objects/picture.hpp`
Class which wraps around raw bytes of a picture.

**Constructor arguments**
- `picture(const std::string filepath)`: Construct from a file path
- `picture(std::ifstream & bytestream)`: Construct using a open file stream
- `picture(std::vector<rapp::types::byte> data)`: Constructor using the raw bytes of a file 
- `picture(const picture &) = default`: Copy constructor

**Methods of the class**
- `picture & operator=(const picture &) = default`: Assignment operator
- `bool operator==(const picture & rhs) const`: Equality operator
- `bool operator!=(const picture & rhs) const`: Inequality operator
- `std::vector<rapp::types::byte> bytearray() const`: Return the array of bytes of the image
- `std::string type() const`: Return image type. Only PNG and JPG supported.
- `bool save(const std::string filepath)`: Save picture to a filepath

##Planned-path
Class `rapp::object::planned_path` in `rapp-api/cpp/objects/planned_path.hpp`
Class which encapsulate collision free path planning service response. *For more information see [path_planning class](#path-planning). 

**Constructor arguments**
- `planned_path(uint8_t plan_found, std::string planning_error, std::vector<pose_stamped> path)`: Constructor using a definition of success/error code `plan_found`, an error description `planning_error` and a vector of [pose_stamped](#pose-stamped) which are the path for the robot `path`.
- `planned_path() = default`: Empty Constructor
- `planned_path(const rapp::object::planned_path &) = default`: Copy constructor
- `planned_path(const json & arg)`: Constructor using JSON

**Methods of the class**
- `json to_json() const`: Return a JSON object
- `bool operator==(const rapp::object::planned_path & rhs) const`: Equality operator
- `uint8_t get_plan() const`: Return the parameter `plan_found`
- `std::string get_error() const`: Return the parameter `planning_error`
- `std::vector<rapp::object::pose_stamped> get_path() const`: Return the parameter `path`

##Point
Class `rapp::object::point` in `rapp-api/cpp/rapp/objects/point.hpp`
Class which encapsulate the point position vector.

**Constructor arguments**
- `point(double x, double y, double z)`: Constructor using code coordinates (x,y,z)
- `point() = default`: Empty constructor
- `point(const rapp::object::point &) = default`: Copy constructor
- `point(const json::const_iterator & position)`: Constructor using JSON 

**Methods of the class**
- `json::object_t to_json() const`: Return a JSON object
- `bool operator==(const rapp::object::point & rhs) const`: Equality operator
- `get_x() const`: Return parameter `x`
- `get_y() const`: Return parameter `y`
- `get_z() const`: Return parameter `z`

##Pose
Class `rapp::object::pose` in `rapp-api/cpp/rapp/objects/pose.hpp`
Class which encapsulates the robot pose vectors (position and orientation).

**Constructor arguments**
- `pose(rapp::object::point position, rapp::object::quaternion orientation)`: Constructor using position and orientation components. The parameter `position` is a vector of position coordinates and the parameter `orientation` is a vector of orientation (quaternion) coordinates.
- `pose() = default`: Empty constructor 
- `pose(const rapp::object::pose &) = default`: Copy constructor
- `pose(const json::const_iterator & pose)`: Constructor using JSON

**Methods of the class**
- `bool operator==(const pose & rhs) const`: Equality operator
- `json::object_t to_json() const`: Return a JSON object
- `rapp::object::point get_position() const`: Return the `position` parameter.
- `rapp::object::quaternion get_orientation() const`: Return the `orientation` parameter.

##Pose-stamped
Class `rapp::object::pose_stamped` in `rapp-api/cpp/rapp/objects/pose_stamped.hpp`
Class which encapsulates the robot pose with message header component.

**Constructor arguments**
     * \brief 
     * \param header defines pose metadata (sequence, frame_id, stamp)
     * \param pose is robot pose definition (position & orientation)
     */
- `pose_stamped(const rapp::object::msg_metadata header, const rapp::object::pose pose)`: Construct using robot pose and message header component. The parameter `header` defines pose metadata (see [msg_metadata class](#msg_metadata)  and the parameter `pose` is the robot pose definition (see [pose class](#pose)).
- `pose_stamped() = default`: Empty constructor
- `pose_stamped(const rapp::object::pose_stamped &) = default`: Copy constructor
- `pose_stamped(const json::const_iterator & stamped)`: Constructor using JSON

**Methods of the class**
- `json::object_t to_json() const`: Return a JSON object
- `rapp::object::msg_metadata get_header() const`: Return a msg_metadata object
- `rapp::object::pose get_pose() const`: Return a pose object
- `bool operator==(const rapp::object::pose_stamped & rhs) const`: Equality operator

##Qr-code
Class `rapp::object::qr_code` in `rapp-api/cpp/rapp/objects/qr_code.hpp`
Class which encapsulates a QR code.

**Constructor arguments**
- `qr_code(float centre_x, float centre_y, std::string label)`: Construct using code coordinates (a rectangle) and a label (URL, email, string, etc). Parameters `centre_x` and `centre_y` are the coordinates and `label` is the message embedded in the QR.
- `qr_code() = default`: Empty constructor
- `qr_code(const qr_code &) = default`: Copy constructor

**Methods of the class**
- `json::object_t to_json() const`: Return a JSON object
- `bool operator==(const qr_code & rhs) const`: Equality operator
- `std::string label() const`: Return the parameter `label`.

##Quaternion
Class `rapp::object::quaternion` in `rapp-api/cpp/rapp/objects/quaternion.hpp`
Class which encapsulates a quaternion vector.

**Constructor arguments**
- `quaternion(double x, double y, double z, double w)`: Constructor using code coordinates (x, y, z, w).
- `quaternion() = default`: Empty constructor
- `quaternion(const rapp::object::quaternion &) = default`: Copy constructor
- `quaternion(const json::const_iterator & orientation)`: Constructor using JSON

**Methods of the class**
- `json::object_t to_json() const`: Return a JSON object
- `bool operator==(const rapp::object::quaternion & rhs) const`: Equality operator
- `get_x() const`: Return parameter `x`
- `get_y() const`: Return parameter `y`
- `get_z() const`: Return parameter `z`
- `get_w() const`: Return parameter `w`

##Time
Class `rapp::object::time` in `rapp-api/cpp/rapp/objects/time.hpp`
Class which wraps arpund time stamp (UNIX Epoch).

**Constructor arguments**
- `time(std::chrono::nanoseconds timepoint)`: Construct using second and nanoseconds. 
- `time() = default`: Empty constructor
- `time(const rapp::object::time &) = default`: Copy constructor
- `time(const json::const_iterator & stamp)`: Constructor using JSON

**Methods of the class**
- `json::object_t to_json() const`: Return a JSON object
- `bool operator==(const rapp::object::time & rhs) const`: Equality operator
- `uint32_t seconds() const`: Return `seconds` parameter
- `uint32_t nanoseconds() const`: Return `nanoseconds` parameter
