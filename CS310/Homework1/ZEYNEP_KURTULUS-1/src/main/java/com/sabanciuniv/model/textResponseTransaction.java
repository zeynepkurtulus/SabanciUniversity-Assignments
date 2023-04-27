package com.sabanciuniv.model;

import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class textResponseTransaction {
	 String message;
	 transactionEmbeddedAccount data;
	 
	 
	 
	public textResponseTransaction() {
		super();
	}
	
	
	
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	public transactionEmbeddedAccount getTransaction() {
		return data;
	}
	public void setTransaction(transactionEmbeddedAccount data) {
		this.data = data;
	}
	public textResponseTransaction(String message, transactionEmbeddedAccount data) {
		super();
		this.message = message;
		this.data = data;
	}
	 
	 
	 
	 
	 
}
