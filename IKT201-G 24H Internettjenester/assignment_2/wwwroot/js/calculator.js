let display = document.getElementById("display");
let clear = document.getElementById("clear");
let reset = document.getElementById("reset");
let back = document.getElementById("back");
let equals = document.getElementById("equals");

let string = "";
let operators = ["+", "-", "*", "/"];

function print() {
    display.value = string;
}

function set_operator(op) {

    if (string.slice(string.length - 1, string.length) == ".") {
        string = string.slice(0, -1);
    }

    // If last index in string is operator, overwrite instead of add new
    for (let i = 0; i < operators.length; i++) {
        if (string.slice(string.length - 1, string.length) == operators[i]) {
            string = string.slice(0, -1);
            break;
        }
    }

    if (string != ""){
        string += op;
    }
    print();
}

function add_number(num) {
    if (num == ".") {
        if (string == "") {
            return;
        }
        for (let i = 0; i < operators.length; i++) {
            if (string.slice(string.length - 1, string.length) == operators[i]) {
                return;
            }
        }
    }
    string += num;
    print();
}

reset.onclick = function () {
    string = "";
    print();
};
clear.onclick = function () {
    let index = -1;
    for (let i = 0; i < operators.length; i++) {
        index = string.indexOf(operators[i]);
        if (index != -1) {
            if (index == string.length - 1) {
                index = -1;
            }
            break;
        }
    }
    string = string.slice(0, index + 1);
    print();
};
back.onclick = function () {
    string = string.slice(0, -1);

    print();
};
equals.onclick = function () {
    if (string == "") {
        return;
    }
    string = eval(string)
    string = string.toString();
    display.value = string ;
    // string = "";
};