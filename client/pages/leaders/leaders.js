getLeaders(leadersArr => {
   leadersArr.forEach(({login, duration}) => {
      duration = parseFloat(duration);
      duration = Math.trunc(duration * 100) / 100;
      leaders.append($(`
         <div class="row jcsb">
            <div>${login}</div>
            <div>${duration}ms</div>
         </div>
      `)[0]);
   });
});