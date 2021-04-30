from typing import MutableMapping
import storage

def multiplayer_handle():
   storage.add_response_handler('connect', on_connect)
   
   
def on_connect(req):
   storage.add_task('loadPage', 'category-select')
   return '{ "status": "OK" }'


def create_multiplayer():
   res = storage.gameload('create-game', {})
   if res['status'] == 'OK':
      storage.gid = res['gid']
   
def connect_multiplayer(gid):
   storage.gid = gid
   start_server()


def start_server():
   storage.run_server()
   storage.gameload('connect', {
      'gid': storage.gid,
      'host': f'{storage.host}:{storage.port}',
   })
 
def stop_server():
   storage.connection_process.terminate()
   
   
def get_gid(callback):
   callback.Call(storage.gid)
   

get_task_counter = 0
def get_tasks(callback):
   global get_task_counter
   get_task_counter += 1
   tasks = storage.get_all_tasks()
   if len(tasks) > 0:
      print('getTasks: some tasks', '; '.join([f'{t[0]}(' + ', '.join(map(str, t[1])) + ')' for t in tasks]))
      callback.Call(tasks)
   else:
      pass
      #print('getTasks: queue is empty ', get_task_counter)
  
  
multiplayer_handle()