

class DictAnswer:
    def __init__(self,many = False, content = {}, error=False, errors={}):
        self.content = content
        self.many = many
        self.error = error
        self.errors = errors
    
    @property
    def get_data(self):
        return {
            "error": self.error,
            "errors": self.errors,
            "many": self.many,
            "content": self.content
        }