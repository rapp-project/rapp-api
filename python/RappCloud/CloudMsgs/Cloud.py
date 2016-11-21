
class CloudMsg(object):
    """ Cloud Message base class implementation. Inherit to implement
    service specific cloud message objects
    """

    def __init__(self, svcname='', **kwargs):
        self._svcname = svcname
        for key, value in kwargs.iteritems():
            if hasattr(self.req, key):
                setattr(self.req, key, value)
            else:
                raise AttributeError(''.join(self.__class__.__name__ +
                    ' object does not have a property named ' + str(key)))


    @property
    def svcname(self):
        return self._svcname




class CloudRequest(object):
    """ Cloud request base class implementation. Inheric to implement
    Cloud Message specific Request objects.
    """
    def __init__(self, **kwargs):
        for key, value in kwargs.iteritems():
            if hasattr(self, key):
                setattr(self, key, value)
            else:
                raise AttributeError(''.join(self.__class__.__name__ +
                    ' object does not have a property named ' + str(key)))


    def __eq__(self, other):
        """! Equality method """
        return self.serialize() == other.serialize()


    def set(self, key, val):
        if hasattr(self, key):
            setattr(self, key, val)


    def make_payload(self):
        """! Abstract method. Return Payload Object.

            @returns Payload - The Payload object
        """
        raise NotImplementedError()


    def make_files(self):
        """! Abstract methor. Return Array of File Objects.

            @returns Array - Array of File Objects.
        """
        raise NotImplementedError()


    def serialize(self):
        """! Serialize CloudRequest object to dictionary.

        @returns Dictionary - Serialized CloudRequest object.
        """
        return { k:v for k,v in vars(self).items() if not k.startswith('_') or callable(v) }




class CloudResponse(object):
    """ Cloud Response base class implementation. Inherit to implement
    Cloud Object specific Response objects.
    """
    def __init__(self, **kwargs):
        for key, val in kwargs.iteritems():
            if hasattr(self, key):
                setattr(self, key, val)
            else:
                raise AttributeError()


    def __eq__(self, other):
        """! Equality method """
        return self.serialize() == other.serialize()


    def set(self, key, val):
        if hasattr(self, key):
            setattr(self, key, val)


    def serialize(self):
        """! Serialize CloudResponse object to dictionary.

        @returns Dictionary - Serialized CloudResponse object.
        """
        return { k:v for k,v in vars(self).items() if not k.startswith('_') or callable(v) }

