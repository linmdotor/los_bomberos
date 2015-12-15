using UnityEngine;
using System.Collections;
using System.Collections.Generic;

[RequireComponent(typeof(BoxCollider))]
[RequireComponent(typeof(Renderer))]

public class FogOfWar : MonoBehaviour {


    public float m_middleAlpha;
    private float m_currentAlpha = 1.0f;

    private bool visited = false;
    private bool visiting = false;

    private Renderer m_renderer;
    private int m_numOfPlayersInSide = 0;

    private List<ParticleSystem> m_firesInSide;

	// Use this for initialization
	void Start () {
        m_renderer = GetComponent<Renderer>();
        m_firesInSide = new List<ParticleSystem>();
	}
	

    void OnTriggerEnter(Collider other)
    {
        if (other.tag.Equals("Player"))
        {
            if (!visiting)
            {
                for (int i = 0; i < m_firesInSide.Count; ++i)
                {
                    if (m_firesInSide[i] != null && m_firesInSide[i].gameObject.activeInHierarchy)
                    {
                        m_firesInSide[i].Play(true);//.enabled = true;
                    }
                    else
                    {
                        m_firesInSide.Remove(m_firesInSide[i--]);
                    }
                }
            }
            visited = true;
            visiting = true;
            m_renderer.material.color = new Color(m_renderer.material.color.r,
                m_renderer.material.color.g, m_renderer.material.color.b, 0.0f);
            ++m_numOfPlayersInSide;
        }
        else if (other.tag.Equals("Fire"))
        {
            m_firesInSide.Add(other.GetComponentInChildren<ParticleSystem>());
            if (!visiting)
            {
                m_firesInSide[m_firesInSide.Count - 1].Play(true);//.enabled = false;
            }
        }
    }
    void OnTriggerExit(Collider other)
    {
        if (other.tag.Equals("Player"))
        {
            if (--m_numOfPlayersInSide < 1)
            {
                m_renderer.material.color = new Color(m_renderer.material.color.r,
                    m_renderer.material.color.g, m_renderer.material.color.b, m_middleAlpha);
                visiting = false;
                for (int i = 0; i < m_firesInSide.Count; ++i)
                {
                    if (m_firesInSide[i] != null && m_firesInSide[i].gameObject.activeInHierarchy)
                    {
                        m_firesInSide[i].Stop(true);//.enabled = false;
                    }
                    else
                    {
                        m_firesInSide.Remove(m_firesInSide[i--]);
                    }
                }
            }
        }
    }
}
