//Fetch JavaScript form objects
let form = document.querySelector('form');
let menuButton = document.querySelector('.menu-button');
let home = document.querySelector('.home-link-c');
let aboutMe = document.querySelector('.about-me-link');
let resume = document.querySelector('.resume-link');
let projects = document.querySelector('.projects-link');
let contactMe = document.querySelector('.contact-me-link');


//Add Hamburger Menu functionality
menuButton.addEventListener('click', handleMenu);
home.addEventListener('click', handleMenu);
aboutMe.addEventListener('click', handleMenu);
resume.addEventListener('click', handleMenu);
projects.addEventListener('click', handleMenu);
contactMe.addEventListener('click', handleMenu);


//Handle menu function.
function handleMenu(event)
{
    let list = document.querySelector('.list');

    if(list.classList.contains('open-nav'))
    {
        list.classList.remove('open-nav');
    }
    else
    {
        list.classList.add('open-nav');
    }
}

//Add event listener to submit button.
form.addEventListener('submit', handleSubmit);

//Function to handle submit.
function handleSubmit(event)
{
    event.preventDefault();

    //Get form element values
    let name = form.elements.name.value;
    let email = form.elements.email.value;
    let message = form.elements.message.value;

    let alertHandeled = 0;

    //Check if reassigned values needed
    if(name == "" & email == "")
    {
        alert("Name and email must be filled out.")
        alertHandeled = 1;
        
    }

    if(name == "")
    {
        name = "no submission";

        if(alertHandeled == 0)
        {
            alert("Name must be filled out.");
        }
    }

    if(email == "")
    {
        email = "no submission";

        if(alertHandeled == 0)
        {
            alert("Email must be filled out.");
        }
    }

    if(message == "")
        message = "no submission";

    //Print values.
    console.log("========= Form Submission =========");
    console.log("Name:", name);
    console.log("Email:", email);
    console.log("Message:", message);
};