// Part 1: Multiple Choice
const answerButtons = document.querySelectorAll(".answer");
const mcqResult = document.getElementById("mcq-result");

answerButtons.forEach(button => {
  button.addEventListener("click", () => {
    // Reset button styles
    answerButtons.forEach(b => b.classList.remove("correct", "incorrect"));
    mcqResult.textContent = "";

    const isCorrect = button.dataset.correct === "true";
    if (isCorrect) {
      button.classList.add("correct");
      mcqResult.textContent = "Correct!";
      button.style.backgroundColor = "#4CAF50";
    } else {
      button.classList.add("incorrect");
      mcqResult.textContent = "Incorrect";
      button.style.backgroundColor = "#f44336";
    }
  });
});

// Part 2: Free Response
const input = document.getElementById("free-response");
const submit = document.getElementById("submit-answer");
const textResult = document.getElementById("text-result");

submit.addEventListener("click", () => {
  const userAnswer = input.value.trim().toLowerCase();
  input.classList.remove("correct", "incorrect");
  textResult.textContent = "";

  if (userAnswer === "paris") {
    input.classList.add("correct");
    textResult.textContent = "Correct!";
    input.style.border = "2px solid #4CAF50" // Green
  } else {
    input.classList.add("incorrect");
    textResult.textContent = "Incorrect";
    input.style.border = "2px solid #f44336" // Red
  }
});
