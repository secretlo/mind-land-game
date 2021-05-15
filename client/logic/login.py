import storage

def set_login_type(login_type):
   storage.login_type = login_type
   
def login(login, password, callback):
   print('From login')
   res = storage.load('/login', {
      'login': login,
      'password': password,
      'type': storage.login_type,
   })
   
   if res['status'] == 'OK':
      storage.id = res['id']
   
   callback.Call(res)
