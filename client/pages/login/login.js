$(buttonLogin).on('click', e => {
   setLoginType('login');
   loadLoginForm();
});
$(buttonRegister).on('click', e => {
   setLoginType('register');
   loadLoginForm();
});

async function loadLoginForm() {
   /** @type {HTMLElement} */
   const brain = $('.brain')[0];
   const animation = brain.animate([
      {top: 97/16+'em'},
      {top: 240/16+'em'},
   ], {
      duration: 1000,
      easing: 'ease',
   });
   await animation.finished;
   loadPage('login-form');
}