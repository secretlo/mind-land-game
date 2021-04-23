import storage

def set_mode(mode):
   storage.mode = mode
   
def get_mode(callback):
   callback.Call(storage.mode)