getWordData((word, description) => {
   window.word = word;
   createLetterBlocks(window.word);
   descriptionElement.textContent = description;
});

getCategory(categoryName => {
   category.textContent = categoryName;
});

function createLetterBlocks(word) {
   word.split('').forEach(letter => {
      $(letters).append($(`<div class="letter letter_closed" data-letter="${letter}"></div>`));
   });
}

let attemptsCounter;
function setAttempts(count) {
   attemptsCounter = count;
   attempts.textContent = count;
}
setAttempts(3);

$(window).on('keyup', e => {
   const letter = e.key.toLowerCase();
   if (["а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"].indexOf(letter) == -1) {
      if (letter.length == 1) alert('Обнаружен ввод не русских символов, смените раскладку');
      return;
   }
 
   if (attemptsCounter == 0) { // attempts ended
      alert('Попытки закончились, попробуйте угадать слово!!');
      return;
   }

   setAttempts(attemptsCounter - 1);
   openLetter(letter, true);
   
   if ($('.letter_closed').length == 0)
      win();
});

function openLetter(letter, withCombo) {
   $(`.letter[data-letter="${letter}"]`).removeClass('letter_closed').each((i, el) => {
      if (withCombo) addCombo();
      el.textContent = el.dataset.letter.toUpperCase();
   });
}

let comboCounter = 0;
function addCombo() {
   comboCounter++;
   if (comboCounter == 3) {
      comboCounter = 0;
      setAttempts(attemptsCounter + 1);
      alert('Вы отгадали 3 буквы!! И за это получаете дополнительную попытку ;)');
   }
}

const gameStart = Date.now();
let gameEnd;

$(guessWord).on('click', e => {
   const guess = prompt('Как думаете, что за слово загадано?').toLowerCase();
   if (guess == window.word)
      win();
});

function win() {
   gameEnd = Date.now();
   alert('Вы угадали слово!! Поздравляем :)');
   sendResult(gameEnd - gameStart);
   window.word.split('').forEach(letter => openLetter(letter, false));
}

function saveResult(gameStart, gameEnd) {
   const duration = gameEnd - gameStart;
   sendResult(duration);
}