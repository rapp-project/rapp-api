

class CloudObject():
    """ Cloud object base class implementation. Inherit to implement
    service specific cloud objects
    """

    def __init__(self, svcname='', **kwargs):
        self._svcname = svcname
        for key, value in kwargs.iteritems():
            if hasattr(self.req, key):
                setattr(self.req, key, value)
            else:
                raise AttributeError()

    @property
    def svcname(self):
        return self._svcname



class CloudRequest():
    """ Cloud request base class implementation. Inheric to implement
    Cloud Object specific Request objects.
    """
    def __init__(self):
        for key, value in kwargs.iteritems():
            if hasattr(self.req, key):
                setattr(self.req, key, value)
            else:
                raise AttributeError()


    def make_payload(self):
        raise NotImplementedError()


    def make_files(self):
        raise NotImplementedError()



class CloudResponse():
    """ Cloud Response base class implementation. Inherit to implement
    Cloud Object specific Response objects.
    """
    def __init__(self, **kwargs):
        for key, value in kwargs.iteritems():
            if hasattr(self.req, key):
                setattr(self.req, key, value)
            else:
                raise AttributeError()


    def serialize(self):
        """ Serialize only public member variables """
        return { k:v for k,v in vars(self).items() if not k.startswith('_') or callable(v) }

