import storage


def game_handle():
   storage.add_response_handler('select-word', on_select_word)
   storage.add_response_handler('letter', on_letter)
   storage.add_response_handler('win', on_win)
   
   
def on_select_word(req):
   storage.swap['word'] = req['word']
   storage.swap['description'] = req['description']
   storage.swap['category'] = req['category']
   
   storage.add_task('loadPage', 'game-multiplayer')
   
   return '{ "status": "OK" }'

def on_letter(req):
   storage.add_task('openLetter', req['letter'], True)
   return '{ "status": "OK" }'

def on_win(req):
   storage.add_task('win')


def select_word():
   if (storage.mode == 'single-player'):
      res = storage.load('/game', {
         'action': 'select-word',
         'category': storage.category,
         'mode': storage.mode,
      })
   else:
      res = storage.load('/game', {
         'action': 'select-word',
         'category': storage.category,
         'mode': storage.mode,
         'gid': storage.gid,
         'id': storage.id,
      })
   
   if res['status'] == 'OK':
      storage.word = res['word']
      storage.description = res['description']
      
def get_word_data(callback):
   if (hasattr(storage, 'word')):
      callback.Call(storage.word, storage.description)
   else:
      callback.Call(storage.swap['word'], storage.swap['description'])
   
def get_category(callback):
   if (hasattr(storage, 'category')):
      callback.Call(storage.category)
   else:
      callback.Call(storage.swap['category'])
  
  
def send_result(duration):
   storage.gameload('result', {
      'duration': duration,
   })
def send_letter(letter):
   storage.gameload('letter', {
      'letter': letter,
      'gid': storage.gid,
      'id': storage.id,
   })
def send_win():
   storage.gameload('win', {
      'gid': storage.gid,
      'id': storage.id,
   })

   
game_handle()