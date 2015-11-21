using UnityEngine;
using System.Collections;

public class Map : MonoBehaviour {

    public uint m_xCell = 4; //casillas en X
    public uint m_zCell = 4; // casillas en Z

    public float m_xSize = 1.0f; //tamano de las celdas en X
    public float m_zSize = 1.0f; //tamano de las celdas en Z

    public bool [][]m_FireMap;
    public Life[][] m_ObjectsMap;

    private bool execution = false;

    void Awake()
    {
        execution = true;

        m_FireMap = new bool[m_xCell][];
        m_ObjectsMap = new Life[m_xCell][];
        for (uint x = 0; x < m_xCell; ++x)
        {
            m_FireMap[x] = new bool[m_zCell];
            m_ObjectsMap[x] = new Life[m_zCell];
            for (uint z = 0; z < m_xCell; ++z)
            {
                m_FireMap[x][z] = false;
                m_ObjectsMap[x][z] = null;
            }
        }
    }
	// Use this for initialization
	void Start () {
        init();
	}
	
    void init()
    {
        
    }

	// Update is called once per frame
	void Update () {
	
	}

    void OnDrawGizmos()
    {
        // Display the explosion radius when selected
        if (execution)
        {
            for (uint x = 0; x < m_xCell; ++x)
            {
                for (uint z = 0; z < m_xCell; ++z)
                {
                    if (m_FireMap[x][z] == true)
                    {
                        if (m_ObjectsMap[x][z] == null)
                        {
                            Gizmos.color = Color.red;
                        }
                        else
                        {
                            Gizmos.color = Color.magenta;
                        }
                    }
                    else
                    {
                        if (m_ObjectsMap[x][z] == null)
                        {
                            Gizmos.color = Color.green;
                        }
                        else
                        {
                            Gizmos.color = Color.blue;
                        }

                    }
                    Gizmos.DrawCube(new Vector3(x * m_xSize + m_xSize * 0.5f, -0.1f, z * m_zSize + m_zSize * 0.5f), new Vector3(m_xSize, 0.2f, m_zSize));
                }
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

    public void addObjectToMap(Vector3 min, Vector3 max, Life life)
    {
        uint xMin = (uint)(min.x / m_xSize);
        uint zMin = (uint)(min.z / m_zSize);

        uint xMax = (uint)(max.x / m_xSize);
        uint zMax = (uint)(max.z / m_zSize);
        for (uint x = xMin; x <= xMax; ++x)
        {
            for (uint z = zMin; z <= zMax; ++z)
            {
                if (x < m_xCell && z < m_zCell)
                {
                    m_ObjectsMap[x][z] = life;
                }
            }
        }
    }
}
