import sys
import threading

from singlifier import *
from browser import *

from logic.login import *
from logic.set_mode import *
from logic.set_category import *
from logic.game import *
from logic.leaders import *
from logic.multiplayer import *

import storage


def main():
    print('Main: main thread is', threading.get_ident())
    
    global singlifier # Global because store HTML of pages, used by Browser to load_page
    singlifier = PageSinglifier() # Constructor do nothing
    singlifier.run() # Generating html files in cache folder

    # All logic is here
    browser = Browser('login', {
        'function': {
            'setLoginType': set_login_type,
            'setMode': set_mode,
            'setCategory': set_category,

            'load': lambda path, data, callback: callback.Call(storage.load(path, data)),
            'login': login,
            
            # game.py
            'selectWord': select_word,
            
            'getWordData': get_word_data,
            'getCategory': get_category,
            'getLeaders': get_leaders,
            'getGid': get_gid,
            'getTasks': get_tasks,
            'getMode': get_mode,
            
            'sendResult': send_result,
            'sendLetter': send_letter,
            'sendWin': send_win,
            
            # multiplayer.py
            'startServer': start_server,
            'stopServer': stop_server,
            
            'createMultiplayer': create_multiplayer,
            'connectMultiplayer': connect_multiplayer,
        }
    }) # Loading browser on 'index' page
    # [data] NO CODE SHOULD BE HERE, BROWSER BLOCK CODE EXECUTION


if __name__ == '__main__':
    main()
