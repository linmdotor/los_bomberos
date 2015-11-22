using UnityEngine;
using System.Collections;

[RequireComponent(typeof(DualStickMovement))]
[RequireComponent(typeof(States))]
[RequireComponent(typeof(Renderer))]
public class Character : MonoBehaviour {
    private string m_Option = null;
    private float m_DeathTime = 10;
    private bool m_OnFire = false;
    public GameObject m_Extinguisher = null;
    public GameObject m_HugeExtinguisher = null;

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
        if (m_OnFire)
        {
            m_DeathTime -= Time.deltaTime;
        }
        if(m_DeathTime < 0)
        {
            isDead();
        }
	}

    void setOption(string option){
        m_Option = option;
        if (m_Option == "FireSuit")
        {
            m_DeathTime += 10;
        }
        if (m_Option == "HugeEx")
        {
            m_HugeExtinguisher.SetActive(true);
            m_Extinguisher.SetActive(false);
        }
    }

    void isDead()
    {
        string name = this.name.ToString();
        gameObject.SendMessage("setDeadPlayer", name);
        this.enabled = false;
    }

    public void useTool()
    {
        if (!axe.enabled && m_Option == "Axe")
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
        gameObject.SendMessage("blockImput", true);
        m_OnFire = true;
    }
    public void OnWater()
    {
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.WET));
        m_renderer.material.color = Color.blue;
        gameObject.SendMessage("blockImput", false);
    }
    public void normalState()
    {
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.NORMAL));
        m_renderer.material.color = Color.white;
        gameObject.SendMessage("blockImput", false);
    }
}
