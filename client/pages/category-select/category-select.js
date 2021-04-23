$('.categories button').on('click', e => {
   setCategory(e.currentTarget.textContent);
   selectWord();
   getMode(mode => {
      if (mode == 'single-player')
         loadPage('game');
      else
         loadPage('game-multiplayer');
   })
});

setInterval(() => {
   getTasks(tasks => {
      if (tasks.length > 0)
         console.log('Running tasks:', tasks);
      for (const [task, args] of tasks) {
         window[task](...args);
      }
   })
}, 100);