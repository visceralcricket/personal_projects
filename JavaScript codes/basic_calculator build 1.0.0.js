function main(){ // Main function
    const prompt = require('prompt-sync')();
    // Prompt the user for input until they provide a non-empty response

    // Input receiving function
    function getNumber(message) {
        let value;
        do {
            value = prompt(message);
        } while (isNaN(value) || value.trim() === '');
        return Number(value);
    }

    // Helpers / required variables
    const num1 = getNumber("Enter the first number: ");
    const num2 = getNumber("Enter the second number: ");
    const operator = prompt("Enter an operator (+, -, *, /");

    let result;
    switch (operator){ // Alternate possible cases => try ; except

        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num2 !== 0 ? num1 / num2 : 'Error: Division by zero';
            break;
        default:
            console.log("Error: Invalid operator");
            return;

    }
    console.log("Result :", result); // Print results
}

main(); // Invoke the main function
