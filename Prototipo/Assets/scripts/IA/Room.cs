using UnityEngine;
using System.Collections;
using System.Collections.Generic;

[RequireComponent(typeof(BoxCollider))]
public class Room : MonoBehaviour {


    public int m_maxFires = 10;
    private int m_numFires = 0;
    private List<Fire> m_fires;
    private Bounds m_bounds;

    void Awake()
    {
        m_fires = new List<Fire>(m_maxFires);
        m_bounds = gameObject.GetComponent<BoxCollider>().bounds;
    }
	// Use this for initialization
	void Start () {
        FireManager.m_instance.addRoom(this);
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public bool belongFire(Vector3 position)
    {
        return m_bounds.Contains(position);
    }
    public bool canAddFire()
    {
        return m_numFires < m_maxFires;
    }
    public void addFire(Fire fire)
    {
        ++m_numFires;
        fire.m_pullOutFire += removeFire;
        m_fires.Add(fire);
    }
    public void removeFire(Fire fire)
    {
        --m_numFires;
        fire.m_pullOutFire -= removeFire;
        m_fires.Remove(fire);
    }
}
