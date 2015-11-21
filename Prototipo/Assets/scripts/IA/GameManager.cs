using UnityEngine;
using System.Collections;

public class GameManager : MonoBehaviour {

    public GameObject[] m_Players = null;
    public static uint m_NumPlayers = 4;
    private bool[] m_DeadPlayers = new bool[m_NumPlayers];
    private uint m_People = 10; //Esto debería ser rellenado por LevelManager.
    private uint m_Cats = 3;    //Esto debería ser rellenado por LevelManager.

	// Use this for initialization
	void Start () {
        for (uint i = 0; i < m_DeadPlayers.Length; ++i)
        {
            m_DeadPlayers[i] = false;
        }
	}
	
	// Update is called once per frame
	void Update () {
        //Éstas comprobaciones son más óptimas como eventos en las correspondientes clases.
        if (m_DeadPlayers[1] && m_DeadPlayers[2] && m_DeadPlayers[4] && m_DeadPlayers[4])
        {
            Application.LoadLevel("GameOver");
        }
        if (m_People + m_Cats == 0)
        {
            Application.LoadLevel("Victory");
        }
	}
}
