using UnityEngine;
using System.Collections;

public class GameManager : MonoBehaviour {

    private static uint m_NumPlayers = 4;
    public static GameManager m_instance = null;
    private uint m_IndexPlayers = 1;
    public GameObject m_Player = null;
    public bool[] m_DeadPlayers = new bool[m_NumPlayers];
    public bool[] m_PlayersReady = new bool[m_NumPlayers];
    public string[] m_Options = new string[m_NumPlayers];
    private uint m_People = 10; //Esto debería ser rellenado por LevelManager.
    private uint m_Cats = 3;    //Esto debería ser rellenado por LevelManager.

	// Use this for initialization
	void Start () {
        if (m_instance == null)
        {
            m_instance = this;
            DontDestroyOnLoad(m_instance);
            for (uint i = 0; i < m_DeadPlayers.Length; ++i)
            {
                m_DeadPlayers[i] = false;
                m_PlayersReady[i] = false;
            }
        }
        else if (m_instance != this)
        {
            Destroy(this.gameObject);
        }
	}
	
	// Update is called once per frame
	void Update () {
        //Éstas comprobaciones son más óptimas como eventos en las correspondientes clases.
        if (m_DeadPlayers[0] && m_DeadPlayers[1] && m_DeadPlayers[2] && m_DeadPlayers[3])
        {
            Application.LoadLevel("GameOver");
        }
        if (m_People + m_Cats == 0)
        {
            Application.LoadLevel("Victory");
        }
        if (m_PlayersReady[0] && m_PlayersReady[1] && m_PlayersReady[2] && m_PlayersReady[3])
        {
            Application.LoadLevel("Level");
            ComenzarPartida(m_Options);
        }
	}



    //Ahora mismo suponemos que solo se elige una opción por personaje al empezar la partida.
    //Modificamos los nombres de los personajes por un número identificador.
    void ComenzarPartida(string[] options){
        GameObject player = Instantiate<GameObject>(m_Player);
        player.SendMessage("setOption", options[m_IndexPlayers]);
        player.name = m_IndexPlayers.ToString();
        ++m_IndexPlayers;
    }

    public void setDeadPlayer(string player)
    {
        m_DeadPlayers[int.Parse(player) - 1] = true;
    }

    public void setReadyPlayer(string player)
    {
        bool ready = m_PlayersReady[int.Parse(player) - 1];
        if (ready)
        {
            ready = false;
        }
        else
        {
            ready = true;
        }
    }

    public void setOptions(string player, string option)
    {
        m_Options[int.Parse(player) - 1] = option;
    }
}
