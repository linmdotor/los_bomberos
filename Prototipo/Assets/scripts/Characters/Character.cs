using UnityEngine;
using System.Collections;

[RequireComponent(typeof(DualStickMovement))]
[RequireComponent(typeof(States))]
public class Character : MonoBehaviour {
    private string m_Option = null;
    private float m_DeathTime = 10; //Cambiar a 10
    private bool m_OnFire = false;
    public GameObject m_Extinguisher = null;
    public GameObject m_HugeExtinguisher = null;
    public GameObject m_helpNotification;
    public Axe axe;
    public float delayToNextTool = 0.5f;
    private DualStickMovement m_dualStickMovement;
    private States m_states;
    public Renderer m_renderer;
    private bool m_toolEnabled = false;
    private bool m_SomebodyNeedHelp = false;
    private Vector3 m_WhereNeedHelp = new Vector3();

    private Transform m_NPC = null;

    public bool m_axeCheat = true;

    public float m_resistanceToBurning = 1.0f;
    public float m_resistanceToBurningRegeneration = 1.0f;
    private float m_currentResistanceToBurning;
    private bool m_FireEnter = false;

    void Awake()
    {
        m_dualStickMovement = GetComponent<DualStickMovement>();
        m_states = GetComponent<States>();
        //m_renderer = GetComponent<Renderer>();
    }
	// Use this for initialization
	void Start () {
        m_currentResistanceToBurning = m_resistanceToBurning;
        axe.enabled = false;
        normalState();
        if (m_axeCheat)
            m_Option = "Axe";
	}
	
	// Update is called once per frame
	void Update () {
        if (m_OnFire)
        {
            m_DeathTime -= Time.deltaTime;
        }
        else
        {
            if (m_FireEnter)
            {
                m_currentResistanceToBurning -= Time.deltaTime;
                if ( m_currentResistanceToBurning < 0.0f)
                {
                    m_currentResistanceToBurning = 0.0f;
                    OnFire();
                }
            }
            else
            {
                m_currentResistanceToBurning += Time.deltaTime * m_resistanceToBurningRegeneration;
                if ( m_currentResistanceToBurning > m_resistanceToBurning)
                {
                    m_currentResistanceToBurning = m_resistanceToBurning;
                }
            }
        }
        if(m_DeathTime < 0)
        {
            isDead();
        }
        if (m_SomebodyNeedHelp && !m_OnFire)
        {
            m_helpNotification.SetActive(true);
            m_helpNotification.transform.LookAt(m_WhereNeedHelp);
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
        gameObject.SetActive(false);
        GameManager.m_instance.setDeadPlayer(this.name);
        //Activar camara otro jugador
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
    public void FireEnter()
    {
        m_FireEnter = true;
    }
    public void FireExit()
    {
        m_FireEnter = false;
    }
    public void OnFire()
    {
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.BURNING));
        m_renderer.material.color = Color.red;
        gameObject.SendMessage("blockImput", true);
        m_OnFire = true;
        //help
        Character[] gos = (Character[])GameObject.FindObjectsOfType<Character>();
        foreach (Character go in gos)
        {
            if (go != this)
            {
                go.SendMessage("setSomeNeedHelp", true);
                go.SendMessage("setWhereNeedHelp", transform.position);
                //go.SendMessage("needHelp", transform.position);
            }
        }
    }
    public void setSomeNeedHelp(bool help)
    {
        m_SomebodyNeedHelp = help;
    }
    public void setWhereNeedHelp(Vector3 posHelp)
    {
        m_WhereNeedHelp = posHelp;
    }
    public void OnWater()
    {
        m_currentResistanceToBurning = m_resistanceToBurning;
        m_FireEnter = false;
        m_OnFire = false;
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.WET));
        m_renderer.material.color = Color.blue;
        gameObject.SendMessage("blockImput", false);
    }
    public void needHelp(Vector3 position)
    {
        m_helpNotification.SetActive(true);
        m_helpNotification.transform.LookAt(position);
    }
    public void normalState()
    {
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.NORMAL));
        m_renderer.material.color = Color.white;
        gameObject.SendMessage("blockImput", false);
    }
    public void pressAction()
    {
        if (m_NPC == null)
        {
            Collider[] hitColliders = Physics.OverlapSphere(transform.position, 3.0f);
            int i = 0;
            while (i < hitColliders.Length)
            {
                if (hitColliders[i].tag.Equals("NPC"))
                {
                    hitColliders[i].transform.SetParent(transform);
                    m_NPC = hitColliders[i].transform;
                    gameObject.SendMessage("blockShoot", true);
                    gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.NPC));
                    return;
                }
                i++;
            }
        }
        else
        {
            m_NPC.parent = null;
            m_NPC = null;
            gameObject.SendMessage("blockShoot", false);
            gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.NORMAL));
        }
    }
    public void dropNPC()
    {
        m_NPC = null;
        gameObject.SendMessage("blockShoot", false);
        gameObject.SendMessage("setSpeed", m_states.changeState(States.CharacterStates.NORMAL));
    }
}
