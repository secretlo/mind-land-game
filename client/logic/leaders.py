import storage

def get_leaders(callback):
   res = storage.load('/leaders', {})
   callback.Call(res['rating'])
