$(buttonResume).on('click', async e => {
   const formData = new FormData(form);
   const res = await new Promise(res => login(formData.get('login'), formData.get('password'), res));

   if (res.status == 'OK')
      loadPage('main-menu');
   else
      alert('Не удалось войти/зарегистрироваться. Попробуйте другой логин или пароль.');
});