using UnityEngine;
using System.Collections;

public class GameManager : MonoBehaviour {
    private uint m_spawnZone = 35;
    public enum GameState { PrevioEscena, Escena }
    private GameState m_Actual = GameState.PrevioEscena;
    public static uint m_NumPlayers = 4;
    public static GameManager m_instance = null;
    public GameObject[] m_Players = null;
    public GameObject[] m_Cameras = null;
    private bool[] m_DeadPlayers = new bool[m_NumPlayers];
    private bool[] m_PlayersReady = new bool[m_NumPlayers];
    private string[] m_Options = new string[m_NumPlayers];
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
            switch (m_Actual)
            {
                case GameState.PrevioEscena:
                    Application.LoadLevel("Apartamentos");
                    m_Actual = GameState.Escena;
                    break;
                case GameState.Escena:
                    ComenzarPartida(m_Options);
                    setReadyOff();
                    break;
                default:
                    break;
            }
        }
	}



    //Ahora mismo suponemos que solo se elige una opción por personaje al empezar la partida.
    //Modificamos los nombres de los personajes por un número identificador.
    void ComenzarPartida(string[] options){
        for (uint i = 0; i < m_NumPlayers; ++i)
        {
            GameObject player = Instantiate<GameObject>(m_Players[i]);
            player.SendMessage("setOption", options[i]);
            player.name = ((GamepadInput.GamePad.Index) i + 1).ToString();
            player.transform.position = new Vector3(m_spawnZone, 0.5f, -7);
            GameObject camera = Instantiate<GameObject>(m_Cameras[i]);
            camera.GetComponent<CameraFollows>().Player = player.transform;
            m_spawnZone += 5;
        }
    }

    public void setDeadPlayer(string player)
    {
        //Dará fallo porque se espera un x donde x es el número del jugador y se recibe la cadena Playerx
        m_DeadPlayers[int.Parse(player) - 1] = true; 

        for (uint i = 0; i < m_DeadPlayers.Length; ++i )
            Debug.Log(m_DeadPlayers[i]);
    }

    public void setReadyPlayer(GamepadInput.GamePad.Index player)
    {
        bool ready = m_PlayersReady[(int)player - 1];
        if (ready)
        {
            m_PlayersReady[(int)player - 1] = false;
        }
        else
        {
            m_PlayersReady[(int)player - 1] = true;
        }
    }

    public void setOptions(GamepadInput.GamePad.Index player, string option)
    {
        m_Options[(int)player - 1] = option;
    }

    void setReadyOff()
    {
        for (uint i = 0; i < m_NumPlayers; ++i)
        {
            m_PlayersReady[i] = false;
        }
    }
}
