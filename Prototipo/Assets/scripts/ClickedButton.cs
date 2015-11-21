using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ClickedButton : MonoBehaviour {
    
    public Dropdown m_Equipment;

    private string[] m_EquipmentList = new string[3];
	// Use this for initialization
	void Start () {
        m_EquipmentList[0] = "Axe";
        m_EquipmentList[0] = "HugeEx";
        m_EquipmentList[0] = "FireSuit";
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void PlayerReady()
    {
        this.SendMessage("setReadyPlayer", this.name);
        object[] options = new object[2];
        options[0] = this.name;
        options[1] = m_EquipmentList[m_Equipment.value];
        this.SendMessage("setOptions", options);
    }
}
