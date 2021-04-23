import storage

def select_word():
   res = storage.load('/game', {
      'action': 'select-word',
      'category': storage.category,
   })
   
   if res['status'] == 'OK':
      storage.word = res['word']
      storage.description = res['description']
      
def get_word_data(callback):
   callback.Call(storage.word, storage.description)
   
def get_category(callback):
   callback.Call(storage.category)
  
  
def send_result(duration):
   storage.gameload('result', {
      'duration': duration,
   })