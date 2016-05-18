# Cloud Messages

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



## CloudMsgs/FaceDetection Message

### File: RappCloud/CloudMsgs/FaceDetection.py

### Request object: FaceDetection.Request

```
# System path to the image file
String imageFilepath

# If true, detection will take less time but it will be less accurate
Bool fast
```

### Response object: FaceDetection.Response

```
# Found faces 2D points. A face is described by an up_left_point and a down_right_point in cartesian coordinates
List faces

# Error message
String error
```

## CloudMsgs/QrDetection Message

### File: RappCloud/CloudMsgs/QrDetection.py

### Request object: QrDetection.Request

```
# System path to the image file
String imageFilepath
```

### Response object: QrDetection.Response

```
# Center points (point2D) of found QR codes
List qr_centers

# Qr description messages of found QR codes (point2D)
List qr_messages

# Error message
String error
```

