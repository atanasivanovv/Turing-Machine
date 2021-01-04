#ifndef __CONTROLLER_CPP
#define __CONTROLLER_CPP

#include "controller.h"

MachineController::MachineController(const std::string& input) : machine(Machine(input)) {}

void MachineController::initializeStates() {
    // ----- Инициализираме състоянията и преходите ----- //

    State* q0 = new State("q0");
    State* q1 = new State("q1");
    State* q2 = new State("q2");
    State* halt = new State("halt");

    machine.addState(q0);
    machine.addState(q1);
    machine.addState(q2);
    machine.addState(halt);

    machine.setCurrentState(q0);
}   

void MachineController::initializeTransitions() {
    // ----- Добавяме състоянията в машината както и преходите между тях ----- //
    Transition* q01 = new Transition('0', '1', 'L', getState("q1"));
    Transition* q02 = new Transition('1', '0', 'R', getState("q2"));
    Transition* q11 = new Transition('0', '0', 'L', getState("q1"));
    Transition* q12 = new Transition('1', '0', 'R', getState("q2"));
    Transition* q21 = new Transition('0', '1', 'H', getState("q2"));
    Transition* q22 = new Transition('1', '1', 'L', getState("halt"));

    machine.findState("q0")->addTransition(q01);
    machine.findState("q0")->addTransition(q02);
    machine.findState("q1")->addTransition(q11);
    machine.findState("q1")->addTransition(q12);
    machine.findState("q2")->addTransition(q21);
    machine.findState("q2")->addTransition(q22);
}

void MachineController::initalizeMachine(const std::string& tape, State* initState) {
    machine = Machine(tape,initState);
}

void MachineController::runMachine() {
    initializeStates();
    initializeTransitions();

    machine.print();
    machine.start();
    machine.print();
    std::cout << "Finished: " << machine.finishedSuccessfuly() << std::endl;
}

State* MachineController::getState(const std::string& s) {
    return machine.findState(s);
}

#endif