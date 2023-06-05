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

namespace TicTacClient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        bool disconnected = false;

        SimpleTcpClient client;
        bool inGame = false;
        bool inQueue = false;
        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                client = new SimpleTcpClient(txtIP.Text); //creates a new instance of a SimpleTcpClient object, passing in the text from a text box named txtIP as the IP address to connect to.
                // initializes listeners for specific server events 
                //client.Events.Connected += Events_Connected;
                client.Events.DataReceived += Events_DataReceived;
                client.Events.Disconnected += Events_Disconnected;
                client.Connect();
                btnConnect.Enabled = false;
                txtName.Enabled = true;
                buttonName.Enabled = true; //*
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error); // shows the message on the text box 
                throw;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Enabled = false;
            btnSend.Enabled = false;
        }

        //function that checks and states whether the server has disconnected 
        private void Events_Disconnected(object sender, ConnectionEventArgs e)
        {
            if (!disconnected)
            {
                this.Invoke((MethodInvoker)delegate
                {
                    txtInfo.Text += $"Server disconnected.{Environment.NewLine}";
                });
            }
        }

        private void Events_DataReceived(object sender, DataReceivedEventArgs e)
        {
            this.Invoke((MethodInvoker)delegate // invokes a delegate on the UI thread so that the text box control can be updated. 
            {
                if (Encoding.UTF8.GetString(e.Data.ToArray()) == "Connected")
                {
                    disconnected = false;
                    button1.Enabled=true;
                    this.Invoke((MethodInvoker)delegate // invokes a delegate on the UI thread so that the text box control can be updated. 
                    {
                        txtInfo.Text += $"Server connected.{Environment.NewLine}"; // appends the text "Server connected" to the rich text box 
                    });
                }
                else if (Encoding.UTF8.GetString(e.Data.ToArray()) == "four")
                {
                    disconnected = true;
                    button1.Enabled = false;
                    btnConnect.Enabled = true;
                    txtName.Enabled = false;
                    buttonName.Enabled = false;
                    client.Disconnect();
                    txtInfo.Text += $"Server Capacity(4) reached.{Environment.NewLine}"; // appends the text "Server connected" to the rich text box 
                }
                else
                {

                    txtInfo.Text += $"Server: {Encoding.UTF8.GetString(e.Data.ToArray())}{Environment.NewLine}"; // appends the text received from the server to the rich text box 
                }
                if (Encoding.UTF8.GetString(e.Data.ToArray()).Contains("You are X for this game.") || Encoding.UTF8.GetString(e.Data.ToArray()).Contains("You are O for this game."))
                {
                    inGame = true;
                    inQueue = false;
                }
                // below lines check if the text received from the server matches any of the four conditions:
                if (Encoding.UTF8.GetString(e.Data.ToArray()).Contains("It's your Turn"))
                {
                    //If the text contains the string "It's your Turn", the btnSend button is enabled so the user can make a move
                    btnSend.Enabled = true;
                }
                else if (Encoding.UTF8.GetString(e.Data.ToArray()) == "Game end")
                {
                    // else if the text equals the string "Game end", the inGame flag is set to false meaning we are not in the game anymore and the btnSend button is enabled.
                    
                    if (!inQueue)
                    {
                        inGame = false;
                        btnSend.Enabled = true;
                    }
                }
                else if (Encoding.UTF8.GetString(e.Data.ToArray()) == "Invalid Username")
                { //  else if If the text equals the string "Invalid Username", the buttonName and txtName controls are both enabled so the user can try again with a different username.
                    buttonName.Enabled = true;
                    txtName.Enabled = true;
                }
                else if (Encoding.UTF8.GetString(e.Data.ToArray()) == "Correct Username")
                {
                    //  If the text equals the string "Correct Username", the btnSend button is enabled meaning the user can now send a message
                    btnSend.Enabled = true;
                }
                else if (Encoding.UTF8.GetString(e.Data.ToArray()) == "Waiting for another player to continue")
                {
                    btnSend.Enabled = true;
                }
            });
        }

        // a function to check and indicate that the Server has connected 
        //private void Events_Connected(object sender, ConnectionEventArgs e)
        //{
        //    
        //}

        //this method handles the requests coming from the clients 
        private void btnSend_Click(object sender, EventArgs e)
        {
            if (client.IsConnected) // This line checks if the client is connected to the server.
            { //below lines checks for the requests of the user like joinign or leaving the game 
                if (txtMessage.Text == "join") //checks if the user's input in the txtMessage text box is equal to the string "join".
                {
                    inQueue = true;
                    client.Send(txtMessage.Text); //send the message "join" to the server
                    txtInfo.Text += $"Me: {txtMessage.Text}{Environment.NewLine}"; // append the text "Me: [message]" to the rich text box
                    txtMessage.Text = string.Empty; // // clear the text box control txtMessage after the user has sent a message to the server this allows the user to type a new message without having to manually delete the old message
                    if (!inGame) // check if the user is already in game, if not 
                    {
                        inGame = true; // make it true so that now the user is in the game
                        btnSend.Enabled = false; //disable the send button 
                    }
                }
                else if (txtMessage.Text == "leave")//checks if the user's input in the txtMessage text box is equal to the string "leave".
                {
                    
                    client.Send(txtMessage.Text); // send the message "leave" to the server
                    txtInfo.Text += $"Me: {txtMessage.Text}{Environment.NewLine}"; // append the text to the rich text box 
                    
                    txtMessage.Text = string.Empty; // clear the text box control txtMessage after the user has sent a message to the server this allows the user to type a new message without having to manually delete the old message
                    if (inGame) // check if the user is in the game, if so 
                    {
                        inGame = false; // since the user is leaving the game set the inGame flag to false 
                    }
                }

                else if (int.TryParse(txtMessage.Text, out int num) && num >= 1 && num <= 9) //checks if the user's input in the txtMessage text box can be parsed as an integer between 1 and 9, inclusive.
                {
                    client.Send(txtMessage.Text); // send the user's input to the server
                    txtInfo.Text += $"Me: {txtMessage.Text}{Environment.NewLine}"; // append the text into rich text box 
                    txtMessage.Text = string.Empty;  // clear the text box control txtMessage after the user has sent a message to the server this allows the user to type a new message without having to manually delete the old message
                    if (inGame) // check if the user in the game, if so:
                    {
                        btnSend.Enabled = false; // disable the send button
                    }
                }
                else if (!string.IsNullOrEmpty(txtMessage.Text)) // checks if the user's input in the txtMessage text box is not null or empty.
                {
                    client.Send(txtMessage.Text); // send the user's input to the server
                    txtInfo.Text += $"Me: {txtMessage.Text}{Environment.NewLine}"; // append the text to the rich text box 
                    txtMessage.Text = string.Empty; //clear the text box control txtMessage after the user has sent a message to the server this allows the user to type a new message without having to manually delete the old message
                }
            }
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void buttonName_Click(object sender, EventArgs e)
        {
            if (client.IsConnected) // check if the client is connected to the server.
            {
                if (!string.IsNullOrEmpty(txtName.Text)) // if the user's input in the txtName text box is not null or empty.
                {
                    var mes = "0001" + txtName.Text; //create a message protocol; if the message starts with 0001 the server understands that the username of the client is actually provided 
                    client.Send(mes); // sends the message stored in mes to the server using the client object.
                    buttonName.Enabled = false;
                    txtName.Enabled = false;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e) //disconnect button
        {
            disconnected = true;
            button1.Enabled = false;
            btnConnect.Enabled = true;
            btnSend.Enabled = false;
            txtName.Enabled = false;
            buttonName.Enabled = false;
            client.Disconnect();
            txtInfo.Text += $"Server disconnected.{Environment.NewLine}"; // appends the text "Server connected" to the rich text box 
        }

        private void button2_Click(object sender, EventArgs e) // clear chat box
        {
            txtInfo.Text = "";
        }
    }
}