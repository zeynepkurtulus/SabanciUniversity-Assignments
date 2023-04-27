package com.sabanciuniv.model;

import org.springframework.data.mongodb.core.mapping.Document;

@Document 
public class textResponse {
	 String message;
	 Account data;
	 
	 public textResponse() {
		 super();
	 }
	 
	public textResponse(String message, Account data) {
		super();
		this.message = message;
		this.data = data;
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

	public Account getAcc() {
		return data;
	}

	public void setAcc(Account data) {
		this.data = data;
	}

	@Override
	public String toString() {
		return "textResponse [message=" + message + ", data=" + data + "]";
	}
	 
	
	
	
	 
}
