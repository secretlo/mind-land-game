$(buttonSinglePlayer).on('click', async e => {
   setMode('single-player');
   loadPage('category-select');
});


$(buttonMultiPlayer).on('click', async e => {
   $(multiPlayerButtons).removeClass('dn');
   $(e.target).addClass('dn');
});


$(buttonCreate).on('click', e => {
   setMode('multi-player');
   createMultiplayer();
   loadPage('multiplayer-wait');
});

$(buttonConnect).on('click', e => {
   const gid = prompt('Введите GID игры');

   if (gid) {
      setMode('multi-player');
      connectMultiplayer(gid);
      loadPage('category-select');
   }
});