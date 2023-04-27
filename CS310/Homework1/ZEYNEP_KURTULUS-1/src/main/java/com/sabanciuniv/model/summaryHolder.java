package com.sabanciuniv.model;

import java.time.LocalDateTime;
import java.util.List;

public class summaryHolder {

	String id;
	String owner;
	LocalDateTime createDate;
	List<transactionEmbeddedAccount> transactionsOut;
	List<transactionEmbeddedAccount> transactionsIn;
	
	Double balance;
	public summaryHolder() {
		super();
	}

	
	public summaryHolder(String owner, LocalDateTime createDate,
			List<transactionEmbeddedAccount> transactionsIn, List<transactionEmbeddedAccount> transactionsOut,
			Double balance) {
		super();
		this.owner = owner;
		this.createDate = createDate;
		this.transactionsOut = transactionsOut;
		this.transactionsIn = transactionsIn;
		this.balance = balance;
	}
	
	
	public summaryHolder(String id, String owner, LocalDateTime createDate, List<transactionEmbeddedAccount> transactionsOut,
			List<transactionEmbeddedAccount> transactionsIn, 
			Double balance) {
		super();
		this.id = id;
		this.owner = owner;
		this.createDate = createDate;
		this.transactionsOut = transactionsOut;
		this.transactionsIn = transactionsIn;
		this.balance = balance;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getOwner() {
		return owner;
	}
	public void setOwner(String owner) {
		this.owner = owner;
	}
	public LocalDateTime getCreateDate() {
		return createDate;
	}
	public void setCreateDate(LocalDateTime createDate) {
		this.createDate = createDate;
	}
	public List<transactionEmbeddedAccount> getTransactionsOut() {
		return transactionsOut;
	}
	
	public List<transactionEmbeddedAccount> getTransactionsIn() {
		return transactionsIn;
	}
	
	public void setTransactionsOut(List<transactionEmbeddedAccount> transactionsOut) {
		this.transactionsOut = transactionsOut;
	}
	
	public void setTransactionsIn(List<transactionEmbeddedAccount> transactionsIn) {
		this.transactionsIn = transactionsIn;
	}
	
	
	public Double getBalance() {
		return balance;
	}
	public void setBalance(Double balance) {
		this.balance = balance;
	}
	
	
	
	
	
	
	
}
