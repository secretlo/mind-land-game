startServer();

getGid(gidNumber => {
   gid.textContent = gidNumber;
});

$(buttonExit).on('click', e => {
   stopServer();
   loadPage('main-menu');
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
