using SuperSimpleTcp;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TicTacToe.Model;



// TICTACTOE SERVER
namespace TicTacToe
{
    public partial class Form1 : Form
    {
        public int playerCount = 0;
        public Form1() 
        {
            InitializeComponent();
        }

        public char[,] table = new char[3, 3];


        public List<Score> ScoreBoard = new List<Score>();
        public List<Player> players = new List<Player>(); // a list of players 
        public List<Player> playerqueue = new List<Player>(); // a player queue for the players waiting to joing the game 
        public List<Player> inGame = new List<Player>(); // a list of players who are currently in the game 

        SimpleTcpServer server;

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            server = new SimpleTcpServer(txtIP.Text);// starts the server with the given socket
            server.Start(); // starts the server
            //initializing specific listeners for client events.
            server.Events.ClientConnected += Events_ClientConnected; 
            server.Events.ClientDisconnected += Events_ClientDisconnected;
            server.Events.DataReceived += Events_DataReceived;
            txtInfo.Text += $"Starting...{Environment.NewLine}"; // sets the message into the rich text box to indicate the server has started 
            btnStart.Enabled = false;
            btnSend.Enabled = true;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            btnSend.Enabled = false;
        }

        public Player FindPlayerBySocket(List<Player> objectList, string socket)
        {
            //a method that returns the player object from the player lists using players socket
            foreach (Player obj in objectList) //  iterates over each Player object in the input list objectList.
            {
                // if the Socket property of the current Player object obj matches the input socket value.
                if (obj.Socket == socket)
                {
                    return obj; // returns the Player objec
                }
            }
            return null; // If the object isn't found, return null
        }

        // a method that finds players by their username 
        public Player FindPlayerByName(List<Player> objectList, string name)
        {
            //a method that returns the player object from the player lists using players name
            foreach (Player obj in objectList) // foreach player 
            {
                if (obj.name == name) // if the name field of the player matches the searched name
                {
                    return obj; // return that player object 
                }
            }
            return null; // If the object isn't found, return null
        }
        public Score FindScoreByName(List<Score> objectList, string name)
        {
            //a method that returns the player object from the player lists using players name
            foreach (Score obj in objectList) // foreach player 
            {
                if (obj.username == name) // if the name field of the player matches the searched name
                {
                    return obj; // return that player object 
                }
            }
            return null; // If the object isn't found, return null
        }

        // a method that finds players by their socket 
        public Player FindOtherPlayerBySocket(List<Player> objectList, string socket)
        {
            //in the inGame list there are two players this method returns the opponent of the client
            foreach (Player obj in objectList) // for each player in the list 
            {
                if (obj.Socket != socket) // if the socket field does not match we have found the opponent 
                {
                    return obj; // return the player object 
                }
            }
            return null; // If the object isn't found, return null
        }

        private void Events_DataReceived(object sender, DataReceivedEventArgs e)
        {   //
            //this method is evoked on client sending data
            //e contains the client's data and its socket

            this.Invoke((MethodInvoker)delegate // use Invoke to run the following code on the UI thread, so that it can safely interact with UI controls.
            {
                // checks if the received data begins with the string "0001". If it does, it assumes that the client is sending their username, and tries to update the player object with that name.
                if (Encoding.UTF8.GetString(e.Data.ToArray()).Length >= 4 && Encoding.UTF8.GetString(e.Data.ToArray()).Substring(0, 4) == "0001")
                {
                    //if the client's data contains 0001 at the beginning it means that the client is sending their usernames
                    var ply = FindPlayerBySocket(players, e.IpPort);
                    string name = Encoding.UTF8.GetString(e.Data.ToArray()).ToString().Substring(4);
                    if (FindPlayerByName(players, name) == null) // if the username is not found i.e. the username is not taken before
                    {
                        ply.name = name; // set the name of the player 
                        server.Send(ply.Socket, "Correct Username"); // state it is a correct username i.e. it is valid 
                        lstClientIP.Items.Add(ply.name); // add the username of the player 
                        Score scr = new Score();
                        scr.lose = 0;
                        scr.score = 0;
                        scr.draw = 0;
                        scr.playCount = 0;
                        scr.username = ply.name;
                        if (FindScoreByName(ScoreBoard, ply.name) != null)
                        {
                            var temp = FindScoreByName(ScoreBoard, ply.name);
                            ScoreBoard.Remove(temp);
                        }
                        ScoreBoard.Add(scr);
                    }
                    else
                    {
                        server.Send(ply.Socket, "Invalid Username"); // if the username is already taken print an error message and do not add the username 
                    }
                }

                //  if the received data is the string "join". If it is, it adds the player to a waiting queue, and waits until there are two players in the queue to start the game.
                else if (Encoding.UTF8.GetString(e.Data.ToArray()) == "join")
                {
                    //if the player is sending a join request the player is put to queue waiting for atleast two players to beging the game.
                    //if there are two players in queue they are put to inGame list
                    var p = FindPlayerBySocket(players, e.IpPort); // stores the socket of the player 
                    txtInfo.Text += $"{p.name}: {Encoding.UTF8.GetString(e.Data.ToArray())}{Environment.NewLine}";//*
                    if (FindPlayerBySocket(playerqueue, e.IpPort) != null) // if we have found the player in the queue he/she cannot re-join bc he/she is already in the queue 
                    {
                        // set the corresponding messages 
                        server.Send(e.IpPort, "You are already in the waiting room. Please wait for another player to join.");
                        txtInfo.Text += $"Server: You are already in the waiting room.{Environment.NewLine}";
                    }
                    else // if the player is not in the queue
                    {
                        playerqueue.Add(FindPlayerBySocket(players, e.IpPort)); // add the player to the queue 
                        if (inGame.Count() != 0) // if there is at least one player already in game
                        {
                            if (FindPlayerBySocket(inGame, e.IpPort) != null) // check if the player requesting to join the is already in the game if so:
                            {
                                // set the corresponding messages 
                                server.Send(e.IpPort, $"You are already in Game");
                                txtInfo.Text += $"Server: You are already in Game.{Environment.NewLine}";
                            }
                            else if (server.IsListening) // if the game has begun, state a message that the player is taken in the waiting queue
                            {
                                if (inGame.Count() == 1)
                                {
                                    server.Send(e.IpPort, "Game is starting soon.");
                                    txtInfo.Text += $"Server: There are 2 players in the waiting room. Game is starting soon.{Environment.NewLine}";
                                    // display the info regarding which player is X and which is O

                                    if (inGame[0].XO == 'X')
                                    {
                                        txtInfo.Text += $"Server: {p.name} is O.{Environment.NewLine}";
                                        p.XO = 'O';
                                        server.Send(p.Socket, "You are O for this game.");
                                        if (!inGame[0].hasTurn)
                                        {
                                            server.Send(p.Socket, "It's your Turn");
                                            p.hasTurn = true;
                                        }
                                        else
                                        {
                                            p.hasTurn = false;
                                        }
                                        inGame.Add(p);
                                        playerqueue.Remove(p);
                                    }
                                    else
                                    {
                                        txtInfo.Text += $"Server: {p.name} is X.{Environment.NewLine}";
                                        p.XO = 'X';
                                        server.Send(p.Socket, "You are X for this game.");
                                        if (!inGame[0].hasTurn)
                                        {
                                            server.Send(p.Socket, "It's your Turn");
                                            p.hasTurn = true;
                                        }
                                        else
                                        {
                                            p.hasTurn = false;
                                        }
                                        inGame.Add(p);
                                        playerqueue.Remove(p);
                                    }
                                }
                                else
                                {

                                    server.Send(e.IpPort, $"The game has already begun. You are in the queue. you are {playerqueue.Count()}. in line");
                                    txtInfo.Text += $"Server: The game has already begun. You are in the queue. you are {playerqueue.Count()}. in line.{Environment.NewLine}";
                                }
                            }

                        }
                        else if (playerqueue.Count() == 1) //if there is only 1 player waiting in the queue the game cannot start 
                        {
                            if (server.IsListening)
                            {

                                // set the corresponding messages
                                server.Send(e.IpPort, "There is only 1 player waiting for the game.");
                                txtInfo.Text += $"Server: There is only 1 player waiting for the game.{Environment.NewLine}";
                                if (inGame.Count() == 1)
                                {
                                    p.XO = (inGame[0].XO == 'X') ? 'Y' : 'X';
                                    server.Send(p.Socket, $"You are {p.XO} for this game.");
                                    if (inGame[0].hasTurn == false)
                                    {
                                        server.Send(p.Socket, "It's your Turn");
                                        p.hasTurn = true;
                                    }
                                    else
                                    {
                                        p.hasTurn = false;
                                    }
                                    inGame.Add(p);
                                }
                            }
                        }
                        else if (playerqueue.Count() == 2) // if there are  players in the queue, now the game can begin
                        {
                            
                            init_Game(playerqueue[0], playerqueue[1]);
                        }
                    }
                }

                else if (Encoding.UTF8.GetString(e.Data.ToArray()) == "leave") // if the client wants to leave the game 
                {// if the client wants to leave the game their opponent wins
                    var p = FindPlayerBySocket(players, e.IpPort); // assign the socket 
                    txtInfo.Text += $"{p.name}: {Encoding.UTF8.GetString(e.Data.ToArray())}{Environment.NewLine}";//*
                    if (FindPlayerBySocket(inGame, e.IpPort) == null) // check using the socket if the player is in the game, if not
                    {
                        //state the corresponding messages 
                        server.Send(e.IpPort, "You are not in the game.");
                        txtInfo.Text += $"Server: You are not in the game.{Environment.NewLine}";
                    }
                    else
                    {
                        // if the player is actually in the game
                        var leavingPlayer = FindPlayerBySocket(players, e.IpPort); // store the socket of the player 
                        var opponent = FindOtherPlayerBySocket(players, e.IpPort);
                        send_Message_All($"{leavingPlayer.name} has left the game. ");
                        if (playerqueue.Count() != 0)
                        {
                            playerqueue[0].XO = leavingPlayer.XO;
                            server.Send(playerqueue[0].Socket, $"You are {leavingPlayer.XO} for this game.");
                            if (leavingPlayer.hasTurn == true)
                            {
                                server.Send(playerqueue[0].Socket, "It's your Turn");
                                playerqueue[0].hasTurn = true;
                            }
                            inGame.Remove(leavingPlayer);
                            inGame.Add(playerqueue[0]);
                            playerqueue.RemoveAt(0);
                        }
                        
                        leavingPlayer.hasTurn = false;
                    }
                }

                //checks if the received data is an integer between 1 and 9 (inclusive), AND 
                //if the player is currently in a game. If both conditions are true, it assumes that the player is making a move in the game.
                else if (int.TryParse(Encoding.UTF8.GetString(e.Data.ToArray()), out int num) && num >= 1 && num <= 9 && FindPlayerBySocket(inGame, e.IpPort) != null && inGame.Count() == 2)
                {
                    var p = FindPlayerBySocket(players, e.IpPort);
                    txtInfo.Text += $"{p.name}: {Encoding.UTF8.GetString(e.Data.ToArray())}{Environment.NewLine}";//*
                    var plyr = FindPlayerBySocket(inGame, e.IpPort);
                    var otherPlayer = FindOtherPlayerBySocket(inGame, e.IpPort);
                    var scr = FindScoreByName(ScoreBoard, plyr.name);
                    var otherPlayerScr = FindScoreByName(ScoreBoard, otherPlayer.name);
                    int row_val = 0;
                    int col_val = 0;
                    string place = Encoding.UTF8.GetString(e.Data.ToArray());

                    // BELOW LINES INCLUDE IMPLEMENTATION OF EACH POSSIBLE MOVE 
                    if (place == "1")
                    {
                        row_val = 0;
                        col_val = 0;
                    }
                    else if (place == "2")
                    {
                        row_val = 0;
                        col_val = 1;
                    }
                    else if (place == "3")
                    {
                        row_val = 0;
                        col_val = 2;
                    }
                    else if (place == "4")
                    {
                        row_val = 1;
                        col_val = 0;
                    }
                    else if (place == "5")
                    {
                        row_val = 1;
                        col_val = 1;
                    }
                    else if (place == "6")
                    {
                        row_val = 1;
                        col_val = 2;
                    }
                    else if (place == "7")
                    {
                        row_val = 2;
                        col_val = 0;
                    }
                    else if (place == "8")
                    {
                        row_val = 2;
                        col_val = 1;
                    }
                    else if (place == "9")
                    {
                        row_val = 2;
                        col_val = 2;
                    }
                    var err = make_move(plyr.XO, table, row_val, col_val, plyr.Socket); //if make move method returns -1 it means that that spot is already filled


                    if (err != -1)
                    {
                        gameState(); // will display the state of the game 


                        if (check_win('X', table)) // checks if X is the winner 
                        {

                            scr.score += 1;
                            scr.playCount += 1;
                            otherPlayerScr.lose += 1;
                            otherPlayerScr.playCount += 1;
                            send_Message_All("Game end");
                            send_Message_All("Winner is X");
                            Game_Over();

                        }
                        else if (check_win('O', table)) // checks if O is te winner 
                        {
                            scr.score += 1;
                            scr.playCount += 1;
                            otherPlayerScr.lose += 1;
                            otherPlayerScr.playCount += 1;
                            send_Message_All("Game end");
                            server.Send(plyr.Socket, "Winner is O");
                            Game_Over();
                        }
                        else if (check_full(table)) // checks if the table is full (at this point we do not have any winner so there is a tie)
                        {
                            scr.draw += 1;
                            scr.playCount += 1;
                            otherPlayerScr.draw += 1;
                            otherPlayerScr.playCount += 1;
                            send_Message_All("Game end");
                            send_Message_All("It is a tie");
                            Game_Over();
                        }
                        else // if there are no winners and no tie ask for the next move to the corresponding player 
                        {
                            var othr = FindOtherPlayerBySocket(inGame, plyr.Socket);
                            server.Send(othr.Socket, "It's your Turn");
                            othr.hasTurn = true;
                        }
                    }
                }
                else
                {//if the message is not a command for the game it is just shown in the servers textbox
                    if (FindPlayerBySocket(inGame, e.IpPort) != null && inGame.Count() == 1)
                    {
                        server.Send(e.IpPort, "Waiting for another player to continue");
                    }
                    var p = FindPlayerBySocket(players, e.IpPort);
                    txtInfo.Text += $"{p.name}: {Encoding.UTF8.GetString(e.Data.ToArray())}{Environment.NewLine}";//*
                }
            });
        }

        private void init_Game(Player player1, Player player2)
        {
            if (server.IsListening)
            {
                // set the corresponding messages
                server.Send(player1.Socket, "Game is starting soon.");
                server.Send(player2.Socket, "Game is starting soon.");
                txtInfo.Text += $"Server: There are 2 players in the waiting room. Game is starting soon.{Environment.NewLine}";
            }
            // display the info regarding which player is X and which is O
            txtInfo.Text += $"Server: {player1.name} is X.{Environment.NewLine}"; // first player in the queue is X 
            txtInfo.Text += $"Server: {player2.name} is O.{Environment.NewLine}"; // second player in the queue is O 
                                                                                  // set the XO fields of the players'
            player1.XO = 'X';
            server.Send(player1.Socket, "You are X for this game.");
            server.Send(player1.Socket, "It's your Turn");
            player1.hasTurn = true;
            playerqueue[1].XO = 'O';
            server.Send(player2.Socket, "You are O for this game.");
            // add the players who are in the game into the inGame list to keep tack of them
            inGame.Add(player1);
            inGame.Add(player2);
            //removing the top two players from the queue since they are in the game now.
            playerqueue.RemoveAt(0);
            playerqueue.RemoveAt(0);
            Game();
        }

        // a method that takes care of ending the inGame list after the game ends 
        private void Game_Over()
        {//after the game ends the inGame list is emptied
            leaderBoard();
            inGame.RemoveAt(0);
            inGame.RemoveAt(0);
            if (playerqueue.Count > 1)
            {
                init_Game(playerqueue[0], playerqueue[1]);
            }
        }


        // a method that is executed when a client disconnectes 
        private void Events_ClientDisconnected(object sender, ConnectionEventArgs e) 
        {
            
            playerCount--; // decrease the count of the players 
            if (FindPlayerBySocket(players, e.IpPort ) != null)
            {
                this.Invoke((MethodInvoker)delegate // // use Invoke to run the following code on the UI thread, so that it can safely interact with UI controls.
                {

                    txtInfo.Text += $"{e.IpPort} disconnected {Environment.NewLine}"; // display the info regarding disconnection
                    var ply = FindPlayerBySocket(players, e.IpPort); // store the socket of that client 
                    lstClientIP.Items.Remove(ply.name);//clients name is deleted from the client names list

                    if (FindPlayerBySocket(inGame, ply.Socket) != null)
                    {//if the client was in game the game ends, the other player is considered to be the winner since the pther player is the only player in the game
                        inGame.Remove(ply); // remove that player 
                        foreach (var player in players)
                        {
                            if (player != ply)
                            {
                                // state the info regaring which player has left the game, which is the winner.
                                server.Send(player.Socket, $"{ply.name} has left the game. ");

                            }

                        }

                        var leavingPlayer = FindPlayerBySocket(players, e.IpPort); // store the socket of the player 
                        var opponent = FindOtherPlayerBySocket(players, e.IpPort);
                        if (playerqueue.Count() != 0)
                        {
                            playerqueue[0].XO = leavingPlayer.XO;
                            server.Send(playerqueue[0].Socket, $"You are {leavingPlayer.XO} for this game.");
                            if (leavingPlayer.hasTurn == true)
                            {
                                server.Send(playerqueue[0].Socket, "It's your Turn");
                                playerqueue[0].hasTurn = true;
                            }
                            inGame.Remove(leavingPlayer);
                            inGame.Add(playerqueue[0]);
                            playerqueue.RemoveAt(0);
                        }
                        
                        leavingPlayer.hasTurn = false;
                    }
                    else if (FindPlayerBySocket(playerqueue, ply.Socket) != null)
                    {//if the client was in queue when disconnected they are removed from the queue
                        playerqueue.Remove(ply);
                    }
                    players.Remove(ply);
                });
            }
        }

        private void Events_ClientConnected(object sender, ConnectionEventArgs e)
        {//this method executed on client connection
         //creates the player object
            playerCount++;
            
            if (playerCount >  4)
	        {
                server.Send(e.IpPort, "four");
	        }
            else
	        {
                this.Invoke((MethodInvoker)delegate
                {
                    server.Send(e.IpPort, "Connected");
                    Player player = new Player();
                    player.Socket = e.IpPort;
                    player.playerNumber = playerCount;
                    player.score = 0;
                    player.lose = 0;
                    player.draw = 0;
                    player.hasTurn = false;
                    players.Add(player);
                    txtInfo.Text += $"{e.IpPort} connected {Environment.NewLine}";
                });
	        }
            
        }

        private void btnSend_Click(object sender, EventArgs e)
        {//this method is executed when server wants to send a message using the server ui.
            if (server.IsListening)
            {
                if (!string.IsNullOrEmpty(txtMessage.Text) && lstClientIP.SelectedItem != null)
                {
                    server.Send(lstClientIP.SelectedItem.ToString(), txtMessage.Text);
                    txtInfo.Text += $"Server: {txtMessage.Text}{Environment.NewLine}";
                    txtMessage.Text = string.Empty;
                }
            }
        }


        // this method checks all conditions that are considered to be a win in the TicTacToe game, it returns true if either of the conidions is satisfied
        private bool check_win(char sign, char[,] table)
        {

            //ROW
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (table[i, j] != sign)
                    {
                        break;
                    }
                    if (j == 2)
                    {
                        return true;
                    }
                }
            }
            //COLUMN
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (table[j, i] != sign)
                    {
                        break;
                    }
                    if (j == 2)
                    {
                        return true;
                    }
                }
            }
            //DIAGONAL
            for (int i = 0; i < 3; i++)
            {
                if (table[i, i] != sign)
                {
                    break;
                }
                if (i == 2)
                {
                    return true;
                }
            }

            //DIAGONAL 2
            for (int i = 0; i < 3; i++)
            {
                if (table[i, 3 - i - 1] != sign)
                {
                    break;
                }
                if (i == 3 - 1)
                {
                    return true;
                }
            }
            return false;
        }


        // a method that checks if the table is full for tie situations and returns true if the table is full
        private bool check_full(char[,] table)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (!(table[i, j] == 'X' || table[i, j] == 'O'))
                    {
                        return false;
                    }
                }
            }

            return true;
        }


        // a method that is used whenever a player makes a move
        private int make_move(char sign, char[,] table, int row, int column, string socket)
        {
            string mes = "";
            var player = FindPlayerBySocket(inGame, socket);
            if (table[row, column] != 'X' && table[row, column] != 'O')
            {
                mes += "Player " + sign + " played on (" + row + "," + column + ")" + $"{Environment.NewLine}";
                send_Message_All(mes);
                table[row, column] = sign;
                player.hasTurn = false;
                return 0;
            }
            else
            {
                server.Send(socket, "This spot is already full");
                txtInfo.Text += $"Server: This spot is already full{Environment.NewLine}";
                server.Send(socket, "It's your Turn");
                txtInfo.Text += $"Server: It's your Turn{Environment.NewLine}";
                return -1;
            }
        }

        private void send_Message_All(string message)
        {//sends message to all players
            foreach (var player in players)
            {
                server.Send(player.Socket, message);
            }
            txtInfo.Text += $"Server: {message}{Environment.NewLine}";
        }


        // a method that displays the current state of the game 
        private void gameState()
        {
            int r, c;
            string message = $"{Environment.NewLine}";
            for (r = 0; r < 3; r++)
            {
                for (c = 0; c < 3; c++)
                {
                    message += table[r, c].ToString() + " ";
                }
                message += $"{Environment.NewLine}";
            }
            send_Message_All(message);
        }


        // a method that displays the number of wins for players 
        private void leaderBoard()
        {
            string message = $"Leaderboard: {Environment.NewLine}";
            foreach (var score in ScoreBoard)
            {

                message += $"{score.username}:   Games: {score.playCount} Wins: {score.score} Lose: {score.lose} Draws: {score.draw} {Environment.NewLine}";
            }
            send_Message_All(message);
        }
        private void Game()
        {
            
            //int row, column;
            int r, c;
            int num = 1;
            for (r = 0; r < 3; r++)
            {
                for (c = 0; c < 3; c++)
                {
                    table[r, c] = (char)(num + 48);
                    num += 1;
                }
            }

            gameState();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtInfo.Text = "";
        }
    }
}
