using UnityEngine;
using System.Collections;

[RequireComponent(typeof(DualStickMovement))]
[RequireComponent(typeof(States))]
[RequireComponent(typeof(Renderer))]
public class Character : MonoBehaviour {

    public Axe axe;
    public float delayToNextTool = 0.5f;
    private DualStickMovement m_dualStickMovement;
    private States m_states;
    private Renderer m_renderer;
    private bool m_toolEnabled = false;

    void Awake()
    {
        m_dualStickMovement = GetComponent<DualStickMovement>();
        m_states = GetComponent<States>();
        m_renderer = GetComponent<Renderer>();
    }
	// Use this for initialization
	void Start () {
        axe.enabled = false;
        normalState();
	}
	
	// Update is called once per frame
	void Update () {
	}

    public void useTool()
    {
        if ( !axe.enabled)
        { 
            axe.enabled = true;
            axe.activeAxe(0.2f);
            StartCoroutine(dissableAxe());
        }
    }
    IEnumerator dissableAxe()
    {
        yield return new WaitForSeconds(delayToNextTool);
        axe.enabled = false;
    }
    public void OnFire()
    {
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.BURNING));
        m_renderer.material.color = Color.red;
    }
    public void OnWater()
    {
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.WET));
        m_renderer.material.color = Color.blue;
    }
    public void normalState()
    {
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.NORMAL));
        m_renderer.material.color = Color.white;
    }
}
