# non-urgent

1. API call `fetch_persona_data` appears to have been deprecated.
2. I do however need either a mysql wrapper, 
3. and potentially a triplet store (for MARIO).
4. create new subdir for all `asio` and call it smth like "core" or "handler"
5. merge computer vision classes into two classes: `recognition` and `detection`
6. merge speech vision classes into two: `recognition` and `detection`

# refactor service calls to apps

The following should be apps, not cloud service calls:

1. news
2. email
3. weather report
4. geolocation
5. why proxy google speech recognition through rapp?
   this should be a direct call from API/Robot to Google, not through the cloud!!!

# critical requirement.

1. I really need a face recongition (not detection) service call,
which can be "individualized" by building a faced database, unique to the user/owner.

2. It would be nice to examine if we can use gait analysis/skeleton tracking from an image
instead of a video stream.
