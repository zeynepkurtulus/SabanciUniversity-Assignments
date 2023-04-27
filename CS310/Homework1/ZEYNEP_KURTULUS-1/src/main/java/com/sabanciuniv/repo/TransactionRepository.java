package com.sabanciuniv.repo;
import java.util.List;

import org.springframework.data.mongodb.repository.MongoRepository;
import com.sabanciuniv.model.Transaction;
import com.sabanciuniv.model.Account;
public interface TransactionRepository extends MongoRepository<Transaction, String>{
	
	public List <Transaction> findBytoAccountId(String str);
	public List <Transaction> findByfromAccountId(String str);
	
	
	

}
