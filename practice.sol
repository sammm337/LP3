// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0

contract BankAccount{
    uint256 public balance;
    address public owner;
    event Deposit(address indexed account , uint256 amount);
    even Withdrawal(address indexed account, uint256 amount);
    constructor{
        owner = msg.sender;
        balance = 0;
    }
    modifier onlyOwner{
        require(msg.sender == owner , "Only owner can perform this transfer");
        _;
    }
    function deposit public payable(){
        require(msg.value > 0 , "Amount should be greater than 0");
        balance += msg.value;
        emit Deposit(msg.sender , msg.value)
    }
    function withdraw public onlyOwner(uint256 amount){
        require(amount > 0, "amount should be positive");
        require(amount <= balance , "Insufficient balance");
        balance -= amount;
        emit Withdrawal(msg.sender, amount);
    }
    function getBalance() public view returns(uint256){
        return balance;
    }
}