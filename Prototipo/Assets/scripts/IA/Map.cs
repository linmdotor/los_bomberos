using UnityEngine;
using System.Collections;

public class Map : MonoBehaviour {

    public uint m_xCell = 4; //casillas en X
    public uint m_zCell = 4; // casillas en Z

    public float m_xSize = 1.0f; //tamano de las celdas en X
    public float m_zSize = 1.0f; //tamano de las celdas en Z

    public bool [][]m_map;

	// Use this for initialization
	void Start () {
        init();
	}
	
    void init()
    {
        m_map = new bool[m_xCell][];
        for (uint x = 0; x < m_xCell; ++x)
        {
            m_map[x] = new bool[m_zCell];
            for (uint z = 0; z < m_xCell; ++z) {
                m_map[x][z] = false;
            }
        }
    }

	// Update is called once per frame
	void Update () {
	
	}

    void OnDrawGizmosSelected()
    {
        // Display the explosion radius when selected
        for (uint x = 0; x < m_xCell; ++x)
        {
            for (uint z = 0; z < m_xCell; ++z)
            {
                if (m_map[x][z] == true)
                {
                    Gizmos.color = Color.red;
                }
                else
                {
                    Gizmos.color = Color.green;
                }
                Gizmos.DrawCube(new Vector3(x * m_xSize + m_xSize * 0.5f, -0.1f, z * m_zSize + m_zSize * 0.5f), new Vector3(m_xSize, 0.2f, m_zSize));
            }
        }
        Gizmos.color = Color.white;
        for (uint z = 0; z <= m_zCell; ++z) {
            Gizmos.DrawLine(new Vector3(0, 0.1f, z * m_zSize), new Vector3(m_xCell * m_xSize, 0.1f, z * m_zSize));
        }
        for (uint x = 0; x <= m_zCell; ++x)
        {
            Gizmos.DrawLine(new Vector3(x * m_xSize, 0.11f, 0), new Vector3(x * m_xSize, 0.1f, m_zCell * m_zSize));
        }
        
    }
}
