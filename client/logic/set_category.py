import storage

def set_category(category):
   storage.category = category
   if storage.mode == 'multi-player':
      storage.gameload('category', {
         'category': storage.category,
      })
      
def on_change_category(req):
   storage.add_task('loadPage', 'game-multiplayer')
   return '{ "status": "OK" }'

storage.add_response_handler('category', on_change_category)
