let passengersEntering = 0;
let passengersExiting = 0;
let passengerspaid = 0; 
let machineOn = false; // Set the initial state to off
let totalAmount = 0;
let menuOptions = ["Select pickup", "Select drop", "Payment", "Exit"];
let pickupStations = [
    "Akurdi Railway Station",
    "Akurdi Police Station",
    "Sambhaji Chowk",
    // ... (add more stations)
];

let selectedPickupStationIndex = -1;
let selectedOptionIndex = -1;

function displayPickupStations() {
    if (machineOn) {
        // Display pickup station options on the screen
        const pickupText = pickupStations.map((station, index) => `${index + 1}. ${station}`).join('<br>');
        document.getElementById('screen').innerHTML = pickupText;

        // Reset selected pickup station
        selectedPickupStationIndex = -1;
    }
}

function selectPickupStation(stationIndex) {
    if (machineOn && stationIndex >= 0 && stationIndex < pickupStations.length) {
        // Store the selected pickup station index for later use
        selectedPickupStationIndex = stationIndex;

        // You can add more logic here to handle the selected station, e.g., store it in a variable.

        // Return to the main screen
        updateScreen();
    }
}

function toggleMachine() {
    machineOn = !machineOn;
    if (!machineOn) {
        // Reset passenger counts when turning off the machine
        passengersEntering = 0;
        passengersExiting = 0;
    }
    updateScreen();
    updatePassengerDisplay();
}

function openMenu() {
    if (machineOn) {
        // Display menu options on the screen with each option on a new line
        const menuText = menuOptions.map((option, index) => `${index + 1}. ${option}<br>`).join('');
        document.getElementById('screen').innerHTML = menuText;

        // Reset selected option
        selectedOptionIndex = -1;
    }
}


function enterMenu() {
    if (machineOn) {
        selectMenuOption(selectedOptionIndex);
    }
}

function selectMenuOption(action) {
    if (machineOn) {
        // Extract the option number from the action (e.g., 'MENU1' -> 1)
        const optionNumber = parseInt(action.replace('MENU', ''));

        // Display different menu options based on the selected option (1, 2, 3, 4)
        switch (optionNumber) {
            case 1:
                // Display Pickup option
                displayPickupStations();
                // Update selected option for further processing
                selectedOptionIndex = 1;
                break;
            case 2:
                // Display Drop option
                displayPickupStations();
                // Update selected option for further processing
                selectedOptionIndex = 2;
                break;
            case 3:
                // Display Payment option
                document.getElementById('screen').innerHTML = "1. Pickup\n2. Drop\n3. Payment\n4. Exit";
                // Update selected option for further processing
                selectedOptionIndex = 3;
                break;
            case 4:
                // Display Exit option and reset to the main screen
                updateScreen();
                // Reset selected option
                selectedOptionIndex = -1;
                break;
            default:
                // Handle unexpected cases
                break;
        }
    }
}

function move(direction) {
    if (machineOn) {
        // Implement movement functionality based on direction
        console.log("Move " + direction);
    }
}

function enter() {
    if (selectedOptionIndex === 1) {
        // If Pickup option is selected, handle entering pickup station
        selectPickupStation(selectedPickupStationIndex);
    } else {
        // Otherwise, handle normal enter functionality
        console.log("Enter");
    }
}

function resetData() {
    if (machineOn) {
        passengersEntering = 0;
        passengersExiting = 0;
        passengersPaid = 0;
        updateScreen();
        console.log("Data reset");
    }
}


function updateScreen(passengersToPay) {
    document.getElementById('screen').innerHTML = machineOn
        ? `Passengers Enter: ${passengersEntering} <br> Passengers Exit: ${passengersExiting} <br> Passengers paid ${passengerspaid 
}`
        : "Machine Off";
}
