using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class FireManager : MonoBehaviour {

    private Map m_map;

    public static FireManager m_instance = null;
    public GameObject fire;

    private PoolManager m_pool;

	// Use this for initialization
	void Start () {
        if (m_instance == null)
        {
            m_instance = this;
            DontDestroyOnLoad(m_instance);
            m_map = gameObject.GetComponent<Map>();
            m_pool = new PoolManager();
            m_pool.goPool = fire;
            m_pool.iPoolAmount = 500;
            m_pool.Init();
            m_pool.Reset();
        }
        else if (m_instance != this)
        {
            Destroy(this.gameObject);
        }
	}
	
	// Update is called once per frame
	void Update () {
	
	}
    public void addFire(Vector3 position)
    {
        int x = (int)(position.x / m_map.m_xSize);
        int z = (int)(position.z / m_map.m_zSize);
        m_map.m_FireMap[x][z] = true;
    }
    public void removeFire(Vector3 position)
    {
        int x = (int)(position.x / m_map.m_xSize);
        int z = (int)(position.z / m_map.m_zSize);
        m_map.m_FireMap[x][z] = false;
    }
    public void firePropagation(Vector3 position, float damegePerPropagationTime)
    {
        int xMin = ((int)(position.x / m_map.m_xSize) - 1);
        int zMin = ((int)(position.z / m_map.m_zSize) - 1);
        if (xMin < 0)
        {
            xMin = 0;
        }
        if (zMin < 0)
        {
            zMin = 0;
        }

        int xMax = ((int)(position.x / m_map.m_xSize) + 1);
        int zMax = ((int)(position.z / m_map.m_zSize) + 1);
        if (xMax >= m_map.m_xCell) xMax = m_map.m_xCell - 1;
        if (zMax >= m_map.m_zCell) zMax = m_map.m_zCell - 1;
        List<Vector2> possibleCell = new List<Vector2>();

        for (int x = xMin; x <= xMax; ++x)
        {
            for (int z = zMin; z <= zMax; ++z)
            {
                if (m_map.m_ObjectsMap[x][z] != null)
                {
                    if (m_map.m_ObjectsMap[x][z].isAlive())
                    {
                        possibleCell.Add(new Vector2(x, z));
                    }
                }
                else if (!m_map.m_FireMap[x][z])
                {
                    possibleCell.Add(new Vector2(x, z));
                }
            }
        }

        if (possibleCell.Count < 1) return;
        int cell = Random.Range(0, possibleCell.Count);
        int xCell = (int)possibleCell[cell].x;
        int zCell = (int)possibleCell[cell].y;
        if (m_map.m_ObjectsMap[xCell][zCell] != null)
        {
            bool dead = m_map.m_ObjectsMap[xCell][zCell].OnDamage(damegePerPropagationTime);
            if (dead)
            {
                //Instantiate(fire, new Vector3(xCell * m_map.m_xSize + m_map.m_xSize * 0.5f, position.y, zCell * m_map.m_zSize + m_map.m_zSize * 0.5f), fire.transform.rotation);
                GameObject go = m_pool.getObject(true);
                go.transform.position = new Vector3(xCell * m_map.m_xSize + m_map.m_xSize * 0.5f, position.y, zCell * m_map.m_zSize + m_map.m_zSize * 0.5f);
                go.transform.rotation = transform.rotation;
                m_map.m_FireMap[xCell][zCell] = true;
            }
        }
        else
        {
            //Instantiate(fire, new Vector3(xCell * m_map.m_xSize + m_map.m_xSize * 0.5f, position.y, zCell * m_map.m_zSize + m_map.m_zSize * 0.5f), fire.transform.rotation);
            GameObject go = m_pool.getObject(true);
            go.transform.position = new Vector3(xCell * m_map.m_xSize + m_map.m_xSize * 0.5f, position.y, zCell * m_map.m_zSize + m_map.m_zSize * 0.5f);
            go.transform.rotation = transform.rotation;
            m_map.m_FireMap[xCell][zCell] = true;
        }

    }


}
