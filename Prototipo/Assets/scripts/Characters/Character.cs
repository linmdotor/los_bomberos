using UnityEngine;
using System.Collections;

[RequireComponent(typeof(DualStickMovement))]
[RequireComponent(typeof(States))]
public class Character : MonoBehaviour {
    public enum HELP_MESSAGES
    {
        HELP_MESSAGES_BURNING, HELP_MESSAGES_FIRE_HERE, HELP_MESSAGES_NPC_HERE, HELP_MESSAGES_MAX
    }

    private string m_Option = null;
    private float m_DeathTime = 10; //Cambiar a 10
    private bool m_OnFire = false;
    public GameObject m_Extinguisher = null;
    public GameObject m_HugeExtinguisher = null;
    public GameObject [] m_helpNotification; //solo permite una notificacion por tipo, si varios piden ayuda se reemplaza
    public float[] helpMessagesDuration;
    private float[] remainingTimeMessages; //solo permite una notificacion por tipo, si varios piden ayuda se reemplaza
    public Axe axe;
    public WaterSword waterSword;
    public float delayToNextTool = 0.5f;
    private DualStickMovement m_dualStickMovement;
    private States m_states;
    public Renderer m_renderer;
    private bool m_toolEnabled = false;
    private Vector3[] m_WhereNeedHelp; //solo permite una notificacion por tipo, si varios piden ayuda se reemplaza

    private Transform m_NPC = null;

    public bool m_axeCheat = false;
    public bool m_waterSwordCheat = true;
    public bool m_HugeExCheat = false;

    public float m_resistanceToBurning = 1.0f;
    public float m_resistanceToBurningRegeneration = 1.0f;
    private float m_currentResistanceToBurning;
    private bool m_FireEnter = false;

    void Awake()
    {
        m_dualStickMovement = GetComponent<DualStickMovement>();
        m_states = GetComponent<States>();
        remainingTimeMessages = new float[(int)HELP_MESSAGES.HELP_MESSAGES_MAX];
        m_WhereNeedHelp = new Vector3[(int)HELP_MESSAGES.HELP_MESSAGES_MAX];
        for (int i=0; i < (int)HELP_MESSAGES.HELP_MESSAGES_MAX; ++i)
        {
            remainingTimeMessages[i] = 0.0f;
        }
        //m_renderer = GetComponent<Renderer>();
    }
	// Use this for initialization
	void Start () {
        m_currentResistanceToBurning = m_resistanceToBurning;
        axe.enabled = false;
        normalState();
        if (m_axeCheat)
            m_Option = "Axe";
        if (m_waterSwordCheat)
            m_Option = "WaterSword";
        if (m_HugeExCheat)
            m_Option = "HugeEx";

        setOption(m_Option);
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
        for (int i = 0; i < (int)HELP_MESSAGES.HELP_MESSAGES_MAX; ++i )
        {
            remainingTimeMessages[i] -= Time.deltaTime;
            if ( remainingTimeMessages[i] > 0.0f)
            {
                //if (!m_OnFire)
                m_helpNotification[i].SetActive(true);
                m_helpNotification[i].transform.LookAt(m_WhereNeedHelp[i]);
            }
            else
            {
                m_helpNotification[i].SetActive(false); //no se debe hacer en cada frame
            }
        }

	}

    public void setOption(string option){
        m_Option = option;
        if (m_Option == "FireSuit")
        {
            m_DeathTime += 10;
        }
        else if (m_Option == "HugeEx")
        {
            m_HugeExtinguisher.SetActive(true);
            m_Extinguisher.SetActive(false);
        }
        else if (m_Option == "Axe")
        {
            //axe.enabled = true; //No es necesario, al utilizar la herramienta ya se comprueba
        }
        else if (m_Option == "WaterSword")
        {
            //waterSword.enabled = true; //No es necesario, al utilizar la herramienta ya se comprueba
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
            axe.gameObject.SetActive(true);
            axe.activeAxe(0.2f);
            StartCoroutine(dissableAxe());
        }
        if (m_Option == "WaterSword")
        {
            waterSword.gameObject.SetActive(true);
            waterSword.activeWaterSword(0.5f);
            StartCoroutine(dissableWaterSword());
        }
    }
    IEnumerator dissableAxe()
    {
        yield return new WaitForSeconds(delayToNextTool);
        axe.gameObject.SetActive(false);
    }
    IEnumerator dissableWaterSword()
    {
        yield return new WaitForSeconds(delayToNextTool);
        waterSword.gameObject.SetActive(false);
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
        helpMessage(HELP_MESSAGES.HELP_MESSAGES_BURNING);
    }
    public void setSomeNeedHelp(object[] args)
    {
        //object[] args = {int action, time };
       remainingTimeMessages[(int)args[0]] = (float)args[1];
    }
    public void setWhereNeedHelp(object[] args)
    {
        //object[] args = {int action, vector3 position };
        m_WhereNeedHelp[(int)args[0]] = (Vector3)args[1];
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
    public void needHelp(Vector3 position) //llamada por fire
    {
        m_helpNotification[(int)HELP_MESSAGES.HELP_MESSAGES_BURNING].SetActive(true);
        m_helpNotification[(int)HELP_MESSAGES.HELP_MESSAGES_BURNING].transform.LookAt(position);
    }
    public void helpMessage(HELP_MESSAGES action)
    {
        Character[] gos = (Character[])GameObject.FindObjectsOfType<Character>();
        foreach (Character go in gos)
        {
            if (go != this)
            {
                object[] args = { action, helpMessagesDuration[(int)action] };
                go.SendMessage("setSomeNeedHelp", args);
                args[1] = transform.position;
                go.SendMessage("setWhereNeedHelp", args);
                //go.SendMessage("needHelp", transform.position);
            }
        }
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
