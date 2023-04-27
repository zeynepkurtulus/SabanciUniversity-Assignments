package com.sabanciuniv.controller;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import com.sabanciuniv.model.Transaction;
import com.sabanciuniv.model.TransactionHelper;
import com.sabanciuniv.model.accountSum;
import com.sabanciuniv.model.summaryHolder;
import com.sabanciuniv.model.textResponse;
import com.sabanciuniv.model.textResponseTransaction;
import com.sabanciuniv.model.transactionEmbeddedAccount;
import com.sabanciuniv.model.Account;
import com.sabanciuniv.repo.AccountRepository;
import com.sabanciuniv.repo.TransactionRepository;

import jakarta.annotation.PostConstruct;

@RestController
@RequestMapping("/bank")
public class BankingRestController {
	@Autowired private AccountRepository accountRepo;
	@Autowired private TransactionRepository transactionRepo;
	
	@PostConstruct
	public void init() { // will be envoked after the autowired section is done
		
		if(accountRepo.count() == 0) { // no elements in the database 
			Account acc1 = new Account("1111","Jack Jones", LocalDateTime.now());
			Account acc2 = new Account ("2222", "Henry Williams", LocalDateTime.now());
			accountRepo.save(acc1);
			accountRepo.save(acc2);
		}
		
		
		if(transactionRepo.count() == 0) { // n0 elements in the database 
			//Account a1 = accountRepo.findById("1111").get();
			//Account a2 = accountRepo.findById("2222").get();
			Transaction trans1 = new Transaction(1500.0, "1111","2222");
			Transaction trans2 = new Transaction(2500.0, "2222", "1111");
			transactionRepo.save(trans1);
			transactionRepo.save(trans2);
		}
		
		
		
		
	}
	
	
	@PostMapping("/account/save")
	public textResponse createAccount(@RequestBody Account account){
		
		if(account.getId() == null) {
			textResponse missingid = new textResponse("Error: missing fields", null);
			return missingid;
		}
		
		else if(account.getOwner() == null) {
			textResponse missingowner = new textResponse("Error: missing fields", null);
			return missingowner;
		}
		
		account.setCreateDate(LocalDateTime.now());
		textResponse savedInfo = new textResponse("Success", account);
		
		accountRepo.save(account);
		
		return savedInfo;
		
	}
	
	@PostMapping("/transaction/save")
	public textResponseTransaction saveTransaction(@RequestBody Transaction trans){
		
		if(trans.getFromAccountId() == null) {
			textResponseTransaction missfrom= new textResponseTransaction("Error: missing fields",null);
			return missfrom;
		}
		
		else if(trans.getToAccountId() == null) {
			textResponseTransaction missto= new textResponseTransaction("Error: missing fields",null);
			return missto;
		}
		
		else if(trans.getAmount() == null) {
			textResponseTransaction missamount= new textResponseTransaction("Error: missing fields",null);
			return missamount;
		}
		
		else if(accountRepo.findByid(trans.getToAccountId()).isEmpty()) {
			textResponseTransaction notexistto= new textResponseTransaction("Error: account id",null);
			return notexistto;
		}
		else if(accountRepo.findByid(trans.getFromAccountId()).isEmpty()) {
			textResponseTransaction notexisfrom = new textResponseTransaction("Error: account id",null);
			return notexisfrom;
		}
		
		transactionEmbeddedAccount transaccount = new transactionEmbeddedAccount(accountRepo.findByid(trans.getFromAccountId()).get(0), 
				accountRepo.findByid(trans.getToAccountId()).get(0), trans.getAmount(), LocalDateTime.now());
		
		textResponseTransaction success= new textResponseTransaction("SUCCESS",transaccount);
		transactionRepo.save(trans);
		return success;
	}
	
	
	
	@GetMapping("transaction/from/{accountId}")
	public TransactionHelper outgiongTransaction(@PathVariable String accountId) {
		
		if(accountRepo.findByid(accountId).get(0) == null) {
			TransactionHelper err1 = new TransactionHelper("ERROR: account does not exists", null);
			return err1;
		}
		String uniqueID = UUID.randomUUID().toString().replace("-", "");
		
		List <transactionEmbeddedAccount> accList = new ArrayList<transactionEmbeddedAccount>();
		List <Transaction> alltrans = transactionRepo.findByfromAccountId(accountId);
		for(Transaction t: alltrans) {
			transactionEmbeddedAccount tacc = new transactionEmbeddedAccount();
			Account a = accountRepo.findByid(t.getToAccountId()).get(0);
			tacc.setTo(a);
			
			Account a2 = accountRepo.findByid(t.getFromAccountId()).get(0);
			tacc.setFrom(a2);
			
			
			tacc.setAmount(t.getAmount());
			tacc.setCreateDate(a2.getCreateDate());
			tacc.setId(uniqueID);
			accList.add(tacc);
		}
		
		TransactionHelper mess = new TransactionHelper("SUCCESS", accList);
		return mess;
	}
	
	
	
	
	
	
	@GetMapping("transaction/to/{accountId}")
	public TransactionHelper incomingTransaction(@PathVariable String accountId) {
		
		if(accountRepo.findByid(accountId).get(0) == null) {
			TransactionHelper err1 = new TransactionHelper("ERROR: account does not exists", null);
			return err1;
		}
		String uniqueID = UUID.randomUUID().toString().replace("-", "");
		List <transactionEmbeddedAccount> accList = new ArrayList<transactionEmbeddedAccount>();
		List <Transaction> alltrans = transactionRepo.findBytoAccountId(accountId);
		
		
		for(Transaction t: alltrans) {
			transactionEmbeddedAccount tacc = new transactionEmbeddedAccount();
			Account a = accountRepo.findByid(t.getFromAccountId()).get(0);
			tacc.setFrom(a);
			
			Account a2 = accountRepo.findByid(t.getToAccountId()).get(0);
			tacc.setTo(a2);
			
			
			tacc.setAmount(t.getAmount());
			tacc.setCreateDate(a.getCreateDate());
			tacc.setId(uniqueID);
			accList.add(tacc);
		}
		
		TransactionHelper mess = new TransactionHelper("SUCCESS", accList);
		return mess;
	}
	
	
	@GetMapping("account/{accountId}")
	public accountSum detailedSummary(@PathVariable String accountId) {
		
		if(accountRepo.findByid(accountId).size() == 0) {
			accountSum message = new accountSum("ERROR: account does not exist", null);
			return message;
		}
		
		else { // if there is an account then store the transactions 
			
			Double balanceHolder = 0.0;
			
			List<Transaction> outgoingTransactionBalance = transactionRepo.findByfromAccountId(accountId); // list contains outgoing transactions --> ok 
			List<Transaction> incomingTransactionBalance = transactionRepo.findBytoAccountId(accountId); // list contains incoming transactions --> ok	
			

			for(Transaction trans: outgoingTransactionBalance) {
				balanceHolder = balanceHolder - trans.getAmount();
			}
			
			for(Transaction trans: incomingTransactionBalance){ //assign the incoming transactions
				balanceHolder = balanceHolder + trans.getAmount();
			}
			
			
			List<transactionEmbeddedAccount> transWithAccFrom = new ArrayList<transactionEmbeddedAccount>(); //from holder : trWitAccList 
			List <Transaction> transFromList = transactionRepo.findByfromAccountId(accountId); //listInn
			String uniqueID1 = UUID.randomUUID().toString().replace("-", "");
			String uniqueID2 = UUID.randomUUID().toString().replace("-", "");
			
			
			for(Transaction trans: transFromList) {
				transactionEmbeddedAccount transWithAccount = new transactionEmbeddedAccount();
				Account accountsto = accountRepo.findByid(trans.getToAccountId()).get(0);
				transWithAccount.setTo(accountsto);
				
				Account accountsfrom = accountRepo.findByid(trans.getFromAccountId()).get(0);
				transWithAccount.setFrom(accountsfrom);
				
				transWithAccount.setAmount(trans.getAmount());
				transWithAccount.setCreateDate(accountsfrom.getCreateDate());
				transWithAccount.setId(uniqueID1);
				transWithAccFrom.add(transWithAccount);
			}
			
			List<transactionEmbeddedAccount> transWithAccTo = new ArrayList<transactionEmbeddedAccount>(); //to holder: trWitAccList1
			List <Transaction> transToList = transactionRepo.findBytoAccountId(accountId); //listIn1
			
			for(Transaction trans: transToList) {
				transactionEmbeddedAccount transWithAccount1 = new transactionEmbeddedAccount();
				Account accountsfrom1 = accountRepo.findByid(trans.getFromAccountId()).get(0);
				transWithAccount1.setFrom(accountsfrom1);

				
				Account accountsto1 = accountRepo.findByid(trans.getToAccountId()).get(0);
				transWithAccount1.setTo(accountsto1);
				
				transWithAccount1.setAmount(trans.getAmount());
				transWithAccount1.setCreateDate(accountsfrom1.getCreateDate());
				transWithAccount1.setId(uniqueID2);
				transWithAccTo.add(transWithAccount1);
				
			}
			
			
			
			
			summaryHolder dataSummary = new summaryHolder(accountRepo.findByid(accountId).get(0).getId(),
					accountRepo.findByid(accountId).get(0).getOwner(),accountRepo.findByid(accountId).get(0).getCreateDate() ,transWithAccFrom, transWithAccTo,  balanceHolder);
			
		
			accountSum aSummary = new accountSum("SUCCES", dataSummary);
			return aSummary;
			
		}
		
		
		
		
	}
	
	
	
	
	
	
	

}
