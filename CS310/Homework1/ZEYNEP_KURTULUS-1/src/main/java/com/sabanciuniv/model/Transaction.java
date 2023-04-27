package com.sabanciuniv.model;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class Transaction {
	
	@Id private String id;
	private Double amount;
	private String fromAccountId;
	private String toAccountId;
	//@DBRef private Account fromAccountId;
	//@DBRef private Account toAccountId;
	
	
	public Transaction(){
		
	
	}
	
	public Transaction(String id, Double amount, String fromAccountId, String toAccountId) {
		super();
		this.id = id;
		this.amount = amount;
		this.fromAccountId = fromAccountId;
		this.toAccountId = toAccountId;
	}
	
	public Transaction(Double amount, String fromAccountId, String toAccountId) {
		super();
		this.amount = amount;
		this.fromAccountId = fromAccountId;
		this.toAccountId = toAccountId;
	}
	
	
	
	
	
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public Double getAmount() {
		return amount;
	}
	public void setAmount(Double amount) {
		this.amount = amount;
	}
	public String getFromAccountId() {
		return fromAccountId;
	}
	public void setFromAccountId(String fromAccountId) {
		this.fromAccountId = fromAccountId;
	}
	public String getToAccountId() {
		return toAccountId;
	}
	public void setToAccountId(String toAccountId) {
		this.toAccountId = toAccountId;
	}
	
	
	
	
	
	
}
