package com.sabanciuniv.model;

import java.time.LocalDateTime;

import org.springframework.data.annotation.Id;

public class transactionEmbeddedAccount {
	@Id String id;
	Account from;
	Account to;
	double amount;
	LocalDateTime createDate;
	
	
	public transactionEmbeddedAccount(){
		super();
	}
	
	
	public transactionEmbeddedAccount(String id, Account from, Account to, double amount, LocalDateTime createDate) {
		super();
		this.id = id;
		this.from = from;
		this.to = to;
		
		
		this.amount = amount;
		this.createDate = createDate;
		
	}
	
	public transactionEmbeddedAccount(Account from, Account to, double amount, LocalDateTime createDate) {
		super();
		
		this.from = from;
		this.to = to;
		this.amount = amount;
		this.createDate = createDate;
	}

	
	
	

	public Account getFrom() {
		return from;
	}

	public void setFrom(Account from) {
		this.from = from;
	}

	public Account getTo() {
		return to;
	}

	public void setTo(Account to) {
		this.to = to;
	}

	public double getAmount() {
		return amount;
	}

	public void setAmount(double amount) {
		this.amount = amount;
	}

	public LocalDateTime getCreateDate() {
		return createDate;
	}

	public void setCreateDate(LocalDateTime createDate) {
		this.createDate = createDate;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	
	
	
	
}
