// Coded by Giulio Bracci for CS50
// Simple page to recreate a Trivia game

// Get the variables to work with: buttons, response and create a map with the correct keys and values for the answers
// Response multiple is the alert bar on the multiple choice section
// Response free is the alert bar on the free choice section

let buttons = document.querySelectorAll(".form__button");
let responseMultiple = document.getElementById("responseMultiple")
let responseFree = document.getElementById("responseFree")
const correctAnswers = new Map().set("touring", "1912").set("youtube", "dating");

// Call the function to generate the events on the page
generateEvents();

// Adds event listeners for click, mouseover and mouseout
function generateEvents()
{
    for (var i = 0 ; i < buttons.length; i++)
    {
        buttons[i].addEventListener("click", function() {let trigger = event.currentTarget; checkAnswer(trigger);});
        buttons[i].addEventListener("mouseover", function() {let trigger__01 = event.currentTarget; trigger__01.classList.add("button__hover");});
        buttons[i].addEventListener("mouseout", function() {let trigger__02 = event.currentTarget; trigger__02.classList.remove("button__hover");});
    }
}

// Checks if the trigger was sent by the free answer section using the trigger.id
function isFreeAnswer(triggerId)
{
    while (triggerId == "answer__free")
    {
        return true;
    }
    return false;
}

// Checks the validity of the answer and then changes the look and feel of the buttons and of the visual response
function checkAnswer(trigger) {

    while (isFreeAnswer(trigger.id) == true)
    {
        // The sibiling of the button is the text bar where we check the value and compare it against the keyword
        // The keyword "dating" has to be present in the free answer in order to return true
        if (trigger.previousElementSibling.value.toLowerCase().includes(correctAnswers.get("youtube")) == true)
        {
            turnGreen(trigger);
            responseFree.textContent = "Correct!";
            responseFree.classList.remove("alert-danger");
            responseFree.classList.add("alert-success");
            setVisible(responseFree);
            trigger.previousElementSibling.value = "";
            return true;
        }
        turnRed(trigger);
        responseFree.textContent = "Incorrect";
        responseFree.classList.remove("alert-success");
        responseFree.classList.add("alert-danger");
        setVisible(responseFree);
        trigger.previousElementSibling.value = "";
        return false;
    }
    // Check the inner text of the button against the value of the key "touring"
    if (trigger.innerText.includes(correctAnswers.get("touring")) == true)
    {
        turnGreen(trigger);
        responseMultiple.textContent = "Correct!";
        responseMultiple.classList.remove("alert-danger");
        responseMultiple.classList.add("alert-success");
        setVisible(responseMultiple);
        return true;
    }
    turnRed(trigger);
    responseMultiple.textContent = "Incorrect";
    responseMultiple.classList.remove("alert-success");
    responseMultiple.classList.add("alert-danger");
    setVisible(responseMultiple);
    return false;
}

// Turns green when the button gets clicked, gets called when checkAnswer returns true
function turnGreen(trigger)
{
    trigger.classList.add("true");setTimeout(function(){trigger.classList.remove("true");},500);
}

// Turns red when the button gets clicked, gets called when checkAnswer returns false
function turnRed(trigger)
{
    trigger.classList.add("false");setTimeout(function(){trigger.classList.remove("false");},500);
}
// Sets visible the response bar for visual feedback, then goes back to hidden
function setVisible(response)
{
    response.classList.add("visible");
    setTimeout(function(){response.classList.remove("visible");response.classList.add("notVisible")},1000);
    response.classList.remove("notVisible");

}










