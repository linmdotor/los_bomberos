using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ClickedButton : MonoBehaviour {
    
    public Dropdown m_Equipment;
    public GamepadInput.GamePad.Index m_Index;

    private string[] m_EquipmentList = new string[4];
	// Use this for initialization
	void Start () {
        m_EquipmentList[0] = "Axe";
        m_EquipmentList[1] = "HugeEx";
        m_EquipmentList[2] = "FireSuit";
        m_EquipmentList[3] = "WaterSword";
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void PlayerReady()
    {
        GameManager.m_instance.setReadyPlayer(m_Index);
        if (gameObject.GetComponent<Image>().color == Color.white)
        {
            gameObject.GetComponent<Image>().color = Color.yellow;
        }
        else
        {
            gameObject.GetComponent<Image>().color = Color.white;
        }
        GameManager.m_instance.setOptions(m_Index, m_EquipmentList[m_Equipment.value]);
    }
}
