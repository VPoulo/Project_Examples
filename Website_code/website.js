//Fetch JavaScript form object
let form = document.querySelector('form');

//Add event listener to submit button.
form.addEventListener('submit', handleSubmit);


//Function to handle submit.
function handleSubmit(event)
{
    event.preventDefault();

    //Get form element values
    let username = form.elements.username.value;
    let email = form.elements.email.value;
    let date = form.elements.date.value;
    let radio_yes = form.elements.yes.checked;
    let radio_no = form.elements.no.checked;
    let radio;

    //Check if reassigned values needed
    if(username == "")
        username = "no submission";

    if(email == "")
        email = "no submission";

    if(date == "")
        date = "no submission";

    if(radio_yes == false & radio_no == false)
        radio = "no submission";
    else if(radio_yes == false)
        radio = "No";
    else
        radio = "Yes";

    //Print values.
    console.log("========= Form Submission =========");
    console.log("Username:", username);
    console.log("Email:", email);
    console.log("Newsletter:", radio);
    console.log("Date:", date);
};